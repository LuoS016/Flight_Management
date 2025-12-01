package main

import (
    "encoding/json"
    "fmt"
    "os"
)

func main() {
    cityCodesFile, err := os.Open("nums.json")
    if err != nil {
        fmt.Printf("无法打开nums.json: %v\n", err)
        fmt.Println("提示: 请确保nums.json文件存在")
        return
    }
    defer cityCodesFile.Close()
    
    var cityCodes []string
    decoder := json.NewDecoder(cityCodesFile)
    err = decoder.Decode(&cityCodes)
    if err != nil {
        fmt.Printf("解析城市代码失败: %v\n", err)
        return
    }
    fmt.Printf("找到 %d 个城市代码\n\n", len(cityCodes))
    flights, err := ScrapeAllFlights(cityCodes)
    if err != nil {
        fmt.Printf("爬取失败: %v\n", err)
        return
    }
    
    fmt.Printf("\n爬取完成！共获取 %d 条航班数据\n\n", len(flights))
    jsonFile, err := os.Create("result.json")
    if err != nil {
        fmt.Printf("无法创建result.json: %v\n", err)
    } else {
        encoder := json.NewEncoder(jsonFile)
        encoder.SetIndent("", "  ")
        err = encoder.Encode(flights)
        jsonFile.Close()
        if err != nil {
            fmt.Printf("保存JSON失败: %v\n", err)
        } else {
            fmt.Println("数据已保存到 result.json\n")
        }
    }
    config, err := loadDatabaseConfig("database.json")
    if err != nil {
        fmt.Printf("加载数据库配置失败: %v\n", err)
        fmt.Println("提示: 请确保 database.json 文件存在且配置正确")
        return
    }
    
    db, err := connectDatabase(config)
    if err != nil {
        fmt.Printf("连接数据库失败: %v\n", err)
        return
    }
    defer db.Close()
    fmt.Println("数据库连接成功\n")
    err = createTable(db)
    if err != nil {
        fmt.Printf("创建表失败: %v\n", err)
        return
    }
    err = clearTable(db)
    if err != nil {
        fmt.Printf(" 清空表失败: %v\n", err)
    } else {
        fmt.Println("旧数据已清空\n")
    }
    sortFlights(flights)
    err = saveFlightsToDatabase(db, flights)
    if err != nil {
        fmt.Printf("保存数据失败: %v\n", err)
        return
    }
    fmt.Printf("   共处理 %d 条航班数据\n", len(flights))
}