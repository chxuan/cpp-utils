#!/usr/bin/env python
# coding=utf-8

import os

# 配置文件路径
file_path="ssh_ip.conf"

# 读取文件
def readlines():
    results = []
    f = open(file_path)
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        if (len(line) != 0):
            results.append(line)

    f.close()
    return results


# 打印IP地址列表
def print_ip_address(ips):
    print("IP地址列表:")
    i = 0
    for line in ips:
        i = i + 1
        print("[" + str(i) + "]:" + line.split(",")[0])


# 选择IP地址
def choice_ip_address():
    i = input("登录到:")
    return i

# 登录到服务器
def login_to_server(ips, i):
    if (i >= 1 and i <= len(ips)):
        arr = ips[i - 1].split(",")
        if (len(arr) == 2):
            os.system("ssh " + arr[1] + "@" + arr[0])
        elif (len(arr) == 3):
            os.system("ssh -p " + arr[1] + " " + arr[2] + "@" + arr[0])
        else:
            print("无效的IP地址或用户名！")
    else:
        print("无效的IP地址或用户名！")
    

# main函数
if __name__ == "__main__":
    ips = readlines()
    print_ip_address(ips)
    i = choice_ip_address()
    login_to_server(ips, i)
