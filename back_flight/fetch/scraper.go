package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strings"
	"time"
)

const url = "https://flights.ctrip.com/schedule/getScheduleByCityPair"

func testurl() {
	requestBody := `{"departureCityCode":"SHA","arriveCityCode":"BJS","pageNo":1}`
	req, err := http.NewRequest("POST", url, strings.NewReader(requestBody))
	if err != nil {
		fmt.Println("Error creating request:", err)
		return
	}
	req.Header.Set("Content-Type", "application/json")
	client := &http.Client{Timeout: 10 * time.Second}
	resp, err := client.Do(req)
	if err != nil {
		fmt.Println("Error making request:", err)
		return
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		fmt.Println("Error reading response body:", err)
		return
	}
	fmt.Println(string(body))
	fmt.Println(len(body))
}
func fetch(departurecity string, arrivecity string, pageno int) (*FlightResponse, error) {
	requestBody := FlightRequest{
		DepartureCityCode: departurecity,
		ArriveCityCode:    arrivecity,
		PageNo:            pageno,
	}
	jsonData, err := json.Marshal(requestBody)
	if err != nil {
		fmt.Println("Error marshalling JSON:", err)
		return nil, err
	}
	req, err := http.NewRequest("POST", url, strings.NewReader(string(jsonData)))
	if err != nil {
		fmt.Println("Error creating request:", err)
		return nil, err
	}
	req.Header.Set("Content-Type", "application/json")
	client := &http.Client{Timeout: 10 * time.Second}
	resp, err := client.Do(req)
	if err != nil {
		fmt.Println("Error making request:", err)
		return nil, err
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		fmt.Println("Error reading response body:", err)
		return nil, err
	}
	var flightResponse FlightResponse
	err = json.Unmarshal(body, &flightResponse)
	if err != nil {
		fmt.Println("Error unmarshalling JSON:", err)
		return nil, err
	}
	fmt.Printf("Total Pages: %d\n", flightResponse.TotalPage)
	fmt.Printf("Departure City: %s\n", flightResponse.DepartureCityName)
	fmt.Printf("Arrival City: %s\n", flightResponse.ArriveCityName)
	for _, schedule := range flightResponse.ScheduleVOList {
		fmt.Printf("Flight No: %s, Depart Date: %s, Depart Time: %s, Arrive Time: %s, Price: %.2f, Depart Port: %s, Arrive Port: %s, Airline: %s\n",
			schedule.FlightNo, schedule.DepartDate, schedule.DepartTime, schedule.ArriveTime,
			schedule.Price, schedule.DepartPortName, schedule.ArrivePortName, schedule.AirlineCompanyName)
	}
	return &flightResponse, nil
}
func minu(t time.Time, num int) time.Time {
	return t.Add(time.Duration(-num) * time.Minute)
}
func convert(ScheduleVO ScheduleVO, depaturecity, arrivecity string) Flight {
	departuretime, _ := time.Parse("2006-01-02 15:04", ScheduleVO.DepartDate+" "+ScheduleVO.DepartTime)
	arrivaltime, _ := time.Parse("2006-01-02 15:04", ScheduleVO.DepartDate+" "+ScheduleVO.ArriveTime)
	if arrivaltime.Before(departuretime) {
		arrivaltime = arrivaltime.Add(24 * time.Hour)
	}
	checkstart := minu(departuretime, 130)
	checkend := minu(departuretime, 10)
	if (ScheduleVO.Price) <= 0 {
		ScheduleVO.Price = 199.0
	}
	flight := Flight{
		FlightNumber:     ScheduleVO.FlightNo,
		DepartureCity:    depaturecity,
		ArrivalCity:      arrivecity,
		DepartureTime:    departuretime,
		ArrivalTime:      arrivaltime,
		Price:            ScheduleVO.Price,
		DepartureAirport: ScheduleVO.DepartPortName,
		ArrivalAirport:   ScheduleVO.ArrivePortName,
		AirlineCompany:   ScheduleVO.AirlineCompanyName,
		CheckinStartTime: checkstart,
		CheckinEndTime:   checkend,
		Status:           "On Time",
	}
	return flight
}
func ScrapeAllFlights(cityCodes []string) ([]Flight, error) {
	var allFlights []Flight

	fmt.Printf("开始爬取，共有 %d 个城市\n", len(cityCodes))
	totalPairs := len(cityCodes) * (len(cityCodes) - 1)
	currentPair := 0
	for i, departureCode := range cityCodes {
		for j, arrivalCode := range cityCodes {
			if i == j {
				continue
			}
			currentPair++
			fmt.Printf("[%d/%d] 正在爬取: %s -> %s",
				currentPair, totalPairs, departureCode, arrivalCode)
			resp, err := fetch(departureCode, arrivalCode, 1)
			if err != nil {
				fmt.Printf(" ... 失败: %v\n", err)
				continue
			}
			if len(resp.ScheduleVOList) == 0 {
				fmt.Printf(" ... 无数据\n")
				continue
			}
			count := 0
			for _, schedule := range resp.ScheduleVOList {
				flight := convert(
					schedule,
					resp.DepartureCityName,
					resp.ArriveCityName,
				)
				allFlights = append(allFlights, flight)
				count++
			}

			fmt.Printf(" ... 成功获取 %d 条航班\n", count)
			time.Sleep(500 * time.Millisecond)
		}
	}

	fmt.Printf("\n共获取 %d 条航班数据\n", len(allFlights))
	return allFlights, nil
}
