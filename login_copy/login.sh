#!/bin/bash

# 配置文件路径
config_file="./login.conf"

# 读取配置文件
function read_config_file()
{
    section=$1
    key=$2
    value=`awk -F '=' '/\['$section'\]/{a=1}a==1&&$1~/'$key'/{print $2;exit}' $config_file`
    echo "$value"
}

# 打印配置列表
function print_item_list()
{
    item_count=100
    echo "IP list:"
    for ((i=1; i<=${item_count}; i++))
    do
        section="item""$i"
        ip=`read_config_file "$section" "ip"`
        if [[ ${ip} != "" ]]; then
            echo "[""$i""]:"${ip}
        fi
    done
}

# 选择连接项
function choice_item()
{
    read -p "login to: " input
    echo ${input}
}

# 登录到服务器
function login_to_server()
{
    item_index=$1
    section="item""$item_index"
    ip=`read_config_file "$section" "ip"`
    user_name=`read_config_file "$section" "user_name"`

    if [[ ${ip} != "" && ${user_name} != "" ]]; then
        ssh "$user_name"@"$ip"
    else
        echo "invaild IP or user name!"
    fi
}

# main函数
function main()
{
    print_item_list
    item_index=`choice_item`
    login_to_server "$item_index"
}

# 调用main函数
main

