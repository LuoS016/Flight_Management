package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"os"
	"sort"

	_ "github.com/alexbrainman/odbc"
)

func loadDatabaseConfig(filename string) (*DatabaseConfig, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("无法打开配置文件: %v", err)
	}
	defer file.Close()

	var config DatabaseConfig
	decoder := json.NewDecoder(file)
	err = decoder.Decode(&config)
	if err != nil {
		return nil, fmt.Errorf("解析配置失败: %v", err)
	}

	return &config, nil
}
func connectDatabase(config *DatabaseConfig) (*sql.DB, error) {
	dsn := fmt.Sprintf("DRIVER={MySQL ODBC 9.5 Unicode Driver};SERVER=%s;PORT=%d;DATABASE=%s;UID=%s;PWD=%s;CHARSET=utf8mb4",
		config.Hostname,
		config.Port,
		config.Database,
		config.Username,
		config.Password,
	)
	db, err := sql.Open("odbc", dsn)
	if err != nil {
		return nil, fmt.Errorf("打开数据库连接失败")
	}
	err = db.Ping()
	if err != nil {
		return nil, fmt.Errorf("数据库连接测试失败")
	}
	return db, nil
}
func createTable(db *sql.DB) error {
	sql := `CREATE TABLE IF NOT EXISTS flight_info (
        flight_id INTEGER PRIMARY KEY AUTO_INCREMENT,
        flight_number VARCHAR(10) NOT NULL,
        departure_city VARCHAR(20) NOT NULL,
        arrival_city VARCHAR(20) NOT NULL,
        departure_time DATETIME NOT NULL,
        arrival_time DATETIME NOT NULL,
        price DECIMAL(10,2) DEFAULT 700,
        departure_airport VARCHAR(20) NOT NULL,
        arrival_airport VARCHAR(20) NOT NULL,
        airline_company VARCHAR(20) NOT NULL,
        checkin_start_time DATETIME NOT NULL,
        checkin_end_time DATETIME NOT NULL,
        status VARCHAR(10) NOT NULL,
        UNIQUE(flight_number)
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci`

	_, err := db.Exec(sql)
	if err != nil {
		return fmt.Errorf("创建表失败: %v", err)
	}

	return nil
}
func clearTable(db *sql.DB) error {
	_, err := db.Exec("DELETE FROM flight_info")
	if err != nil {
		return fmt.Errorf("清空表失败: %v", err)
	}
	return nil
}
func sortFlights(flights []Flight) {
	sort.Slice(flights, func(i, j int) bool {
		if flights[i].DepartureTime.Equal(flights[j].DepartureTime) {
			return flights[i].ArrivalTime.Before(flights[j].ArrivalTime)
		}
		return flights[i].DepartureTime.Before(flights[j].DepartureTime)
	})
}
func saveFlightsToDatabase(db *sql.DB, flights []Flight) error {
	sql := `INSERT INTO flight_info 
        (flight_number, departure_city, arrival_city, departure_time, arrival_time,
         price, departure_airport, arrival_airport, airline_company,
         checkin_start_time, checkin_end_time, status)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)`

	successCount := 0
	failCount := 0

	for _, flight := range flights {
		_, err := db.Exec(sql,
			flight.FlightNumber,
			flight.DepartureCity,
			flight.ArrivalCity,
			flight.DepartureTime,
			flight.ArrivalTime,
			flight.Price,
			flight.DepartureAirport,
			flight.ArrivalAirport,
			flight.AirlineCompany,
			flight.CheckinStartTime,
			flight.CheckinEndTime,
			flight.Status,
		)
		if err != nil {
			failCount++
			if failCount <= 5 {
				fmt.Printf("  插入失败: %s - %v\n", flight.FlightNumber, err)
			}
			continue
		}
		successCount++
	}

	fmt.Printf("数据库保存完成: 成功 %d 条, 失败 %d 条\n", successCount, failCount)
	return nil
}
