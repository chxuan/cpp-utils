#!/bin/bash

# 配置文件路径
config_file="/usr/local/etc/ssh_ip.conf"

# 读取配置文件
function read_config_file()
{
    section=$1
    key=$2
    value=`awk -F '=' '/\['$section'\]/{a=1}a==1&&$1~/'$key'/{print $2;exit}' $config_file`
    echo "$value"
}

# 打印IP地址列表
function print_ip_address()
{
    item_count=20
    echo "IP地址列表:"
    for ((i=1; i<=${item_count}; i++))
    do
        section="item""$i"
        ip=`read_config_file "$section" "ip"`
        if [[ ${ip} != "" ]]; then
            echo "[""$i""]:"${ip}
        fi
    done
}

# 选择IP地址
function choice_ip_address()
{
    read -p "登录到:" input
    echo ${input}
}

# 登录到服务器
function login_to_server()
{
    item_index=$1
    section="item""$item_index"
    ip=`read_config_file "$section" "ip"`
    port=`read_config_file "$section" "port"`
    user_name=`read_config_file "$section" "user_name"`

    if [[ ${ip} != "" && ${port} != "" && ${user_name} != "" ]]; then
        ssh -p $port "$user_name"@"$ip"
    else
        echo "无效的IP地址或用户名！"
    fi
}

# main函数
function main()
{
    print_ip_address
    item_index=`choice_ip_address`
    login_to_server "$item_index"
}

# 调用main函数
main

