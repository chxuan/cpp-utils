#!/bin/bash

# 配置文件路径
config_file="./copy.conf"

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
    read -p "connect to:" input
    echo ${input}
}

# 选择拷贝方向
function choice_direction()
{
    read -p $'[1]:to remote\n[2]:to location\nchoice direction: ' direction
    echo ${direction}
}

# 选择拷贝的文件
function choice_file()
{
    read -p "choice file path: " file_name
    echo ${file_name}
}

# 拷贝文件
function copy_file()
{
    item_index=$1
    section="item""$item_index"
    ip=`read_config_file "$section" "ip"`
    user_name=`read_config_file "$section" "user_name"`

    if [[ ${ip} != "" && ${user_name} != "" ]]; then
        direction=$2
        file_name=$3
        if [ ${direction} == 1 ]; then
            scp "$file_name" "$user_name"@"$ip":~
            # echo "$file_name"
            # scp ~/b.tar.gz "$user_name"@"$ip":~
        else
            scp "$user_name"@"$ip:$file_name" ~
        fi
    else
        echo "invaild IP or user name!"
    fi
}

# main函数
function main()
{
    print_item_list
    item_index=`choice_item`
    direction=`choice_direction`
    file_name=`choice_file`
    copy_file "$item_index" "$direction" "$file_name"
}

# 调用main函数
main

