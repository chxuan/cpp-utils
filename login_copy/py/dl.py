#!/usr/bin/env python
# coding=utf-8

import os
import sys

# 配置文件路径
file_path="/usr/local/etc/ssh_ip.conf"
# 文件保存路径
save_path="~/cx"

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
    print '\033[1;32m%-10s %-20s %-10s %-15s %9s\033[0m' % ("ID", "IP", "PORT", "用户名", "备注")
    i = 0
    for line in ips:
        i = i + 1
        arr = line.split(",")
        print '%-10d %-20s %-10s %-15s %s' % (i, arr[0], arr[1], arr[2], arr[3])


# 选择IP地址
def choice_ip_address():
    i = input("从哪里下载:")
    return i


# 下载文件
def download_file(ips, i, filenames):
    if (i >= 1 and i <= len(ips)):
        arr = ips[i - 1].split(",")
        os.system("scp -P " + arr[1] + " -r " + arr[2] + "@" + arr[0] + ":" + filenames + " " + save_path)
        print(filenames + "已经下载到" + save_path)
    else:
        print("无效的IP地址或用户名！")
    

# main函数
if __name__ == "__main__":
    if (len(sys.argv) > 1):
        filenames = ""
        for filename in sys.argv[1:]:
            if (len(filenames) == 0):
                filenames = filenames + filename
            else:
                filenames = filenames + " " + filename

        filenames = "'" + filenames + "'"
        ips = readlines()
        print_ip_address(ips)
        i = choice_ip_address()
        download_file(ips, i, filenames)
    else:
        print("请输入文件名！")
