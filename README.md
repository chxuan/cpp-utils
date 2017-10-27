samples
===================

个人博客：http://chengxuan.me/
cnblogs：http://www.cnblogs.com/highway-9/


服务器端口整理
===============================================

## 路由器端口映射

| 协议          | 公网端口 | 内网端口 |
| -------       | -----    | ------   |
| 博实结(bsj)   | 6688     | 52929    |
| 康凯斯(kks)   | 6682     | 52926    |
| 国标(gb)      | 6685     | 52928    |
| 天琴(tq)      | 7777     | 57777    |
| 自研设备(lxt) | 52931    | 52931    |

## 接入服务器
>接收来自设备上报的位置、报警二进制数据。

| 服务器名   | 设备数据端口 | 监听端口 |
| -------    | -----        | ------   |
| access_bsj | 52929        | 48019    |
| access_kks | 52926        | 48025    |
| access_gb  | 52928        | 48022    |
| access_tq  | 57777        | 48021    |
| access_lxt | 52931        | 48036    |


## 协转服务器
>接收接入服务器的数据，将二进制数据转换成ProtocolBuffer协议，起到协议转换作用。

| 服务器名  | 监听端口 | 连接端口 |
| -------   | -----    | ------   |
| parse_bsj | 48302    | 48019    |
| parse_kks | 48305    | 48025    |
| parse_gb  | 48303    | 48022    |
| parse_tq  | 48301    | 48021    |
| parse_lxt | 48309    | 48036    |

## 分发服务器
>接收协转服务器的数据，对数据进行简单清洗和计算（计算里程、停车时间等），并将数据分发到其他服务器。

| 服务器名         | 监听端口 | 连接端口                                  |
| -------          | -----    | ------                                    |
| deliver_vehicle  | 58002    | 48301 48302 48303 48305 48309 39007 48006 |
| deliver_terminal | 48002    | 48301 48302 48303 48305 48309 39003 48006 |


## 查询服务器
>连接mongo数据库，并提供车辆、设备的位置、报警等数据查询功能。

| 服务器名       | 监听端口 | 连接端口 |
| -------        | -----    | ------   |
| query_vehicle  | 39007    | --       |
| query_terminal | 39003    | --       |

## 存储服务器
>接收分发服务器的数据，并将数据写入mongo数据库。

| 服务器名       | 监听端口 | 连接端口 |
| -------        | -----    | ------   |
| store_vehicle  | --       | 58002    |
| store_terminal | --       | 48102    |

## 数据中心服务器
>业务核心服务器，所有的关系数据都会通过该服务器写入mysql并同步到其他服务器。

| 服务器名    | 监听端口                                                    | 连接端口 |
| -------     | -----                                                       | ------   |
| data_center | 48006 48008 48009 48011 48012 48020 48013 48014 48016 48024 | --       |

## 监控规则服务器
>接收来自分发服务器的数据，并对车辆数据进行监控，该服务器提供了碰撞、震动、原地设防等监控规则，触发的规则信息将发送到数据中心服务器。

| 服务器名 | 监听端口 | 连接端口          |
| -------  | -----    | ------            |
| monitor  | --       | 58002 48012 39007 |

## 命令服务器
>接收来自数据中心服务器的命令数据，并将ProtocolBuffer协议转换成设备二进制数据，发送到接入服务器，由接入服务器发送给设备，该服务器提供了查询设备版本、状态、点名等指令。

| 服务器名 | 监听端口 | 连接端口                            |
| -------  | -----    | ------                              |
| command  | --       | 48019 48021 48022 48025 48036 48020 |

## 用车报告服务器
>将所有车辆数据生成用车报告（包含里程、开车时间、最大速度等数据），并发送到数据中心服务器。

| 服务器名       | 监听端口 | 连接端口 |
| -------        | -----    | ------   |
| vehicle_report | 48308    | 48011    |

## 推送服务器
>接收来自分发和数据中心服务器的数据，并将数据推送到代理服务器。

| 服务器名      | 监听端口          | 连接端口    |
| -------       | -----             | ------      |
| push_vehicle  | 58004 58007       | 48009 58002 |
| push_terminal | 48004 48017 58008 | 48009 48002 |

## 代理服务器
>对客户端提供访问内部服务器的权限，客户端与内部服务器的交互都会通过代理服务器，其中客户端包含手机app、宙斯ERP、欣悦途、风控系统。

| 服务器名             | 监听端口 | 连接端口                                              |
| -------              | -----    | ------                                                |
| agent_app            | 58001    | 48014 48013 48002 58002 39007 58004 48017 48308       |
| agent_ticket         | 58009    | 48013 48014 48002 58002 48017 58004 39003 39007 48018 |
| agent_xyt            | 58010    | 48014 48013 48002 58002 39007 58004 48017 48308       |
| agent_vehicle_proto  | 58105    | 48008 48016 48002 58002 39007 58007 58004             |
| agent_terminal_proto | 48110    | 48013 48002 39003 48017 48004                         |

## 其他服务

| 名称                 | IP           | 端口   |
| -------              | -----        | ------ |
| rabbitmq             | 192.168.1.29 | 5672   |
| k3k6-server          | 192.168.1.66 | 48018  |
| mongo                | 192.168.1.71 | 50001  |
| mysql(data_center)   | 192.168.1.97 | 3306   |
| mysql(data_analysis) | 192.168.1.97 | 3306   |
| mysql(data_transfer) | 192.168.1.96 | 3306   |


# 欢迎使用 Cmd Markdown 编辑阅读器

------

我们理解您需要更便捷更高效的工具记录思想，整理笔记、知识，并将其中承载的价值传播给他人，**Cmd Markdown** 是我们给出的答案 —— 我们为记录思想和分享知识提供更专业的工具。 您可以使用 Cmd Markdown：

> * 整理知识，学习笔记
> * 发布日记，杂文，所见所想
> * 撰写发布技术文稿（代码支持）
> * 撰写发布学术论文（LaTeX 公式支持）

![cmd-markdown-logo](https://www.zybuluo.com/static/img/logo.png)

除了您现在看到的这个 Cmd Markdown 在线版本，您还可以前往以下网址下载：

### [Windows/Mac/Linux 全平台客户端](https://www.zybuluo.com/cmd/)

> 请保留此份 Cmd Markdown 的欢迎稿兼使用说明，如需撰写新稿件，点击顶部工具栏右侧的 <i class="icon-file"></i> **新文稿** 或者使用快捷键 `Ctrl+Alt+N`。

------

## 什么是 Markdown

Markdown 是一种方便记忆、书写的纯文本标记语言，用户可以使用这些标记符号以最小的输入代价生成极富表现力的文档：譬如您正在阅读的这份文档。它使用简单的符号标记不同的标题，分割不同的段落，**粗体** 或者 *斜体* 某些文字，更棒的是，它还可以

### 1. 制作一份待办事宜 [Todo 列表](https://www.zybuluo.com/mdeditor?url=https://www.zybuluo.com/static/editor/md-help.markdown#13-待办事宜-todo-列表)

- [ ] 支持以 PDF 格式导出文稿
- [ ] 改进 Cmd 渲染算法，使用局部渲染技术提高渲染效率
- [x] 新增 Todo 列表功能
- [x] 修复 LaTex 公式渲染问题
- [x] 新增 LaTex 公式编号功能

### 2. 书写一个质能守恒公式[^LaTeX]

$$E=mc^2$$

### 3. 高亮一段代码[^code]

```python
@requires_authorization
class SomeClass:
    pass

if __name__ == '__main__':
    # A comment
    print 'hello world'
```

### 4. 高效绘制 [流程图](https://www.zybuluo.com/mdeditor?url=https://www.zybuluo.com/static/editor/md-help.markdown#7-流程图)

```flow
st=>start: Start
op=>operation: Your Operation
cond=>condition: Yes or No?
e=>end

st->op->cond
cond(yes)->e
cond(no)->op
```

### 5. 高效绘制 [序列图](https://www.zybuluo.com/mdeditor?url=https://www.zybuluo.com/static/editor/md-help.markdown#8-序列图)

```seq
Alice->Bob: Hello Bob, how are you?
Note right of Bob: Bob thinks
Bob-->Alice: I am good thanks!
```

### 6. 高效绘制 [甘特图](https://www.zybuluo.com/mdeditor?url=https://www.zybuluo.com/static/editor/md-help.markdown#9-甘特图)

```gantt
    title 项目开发流程
    section 项目确定
        需求分析       :a1, 2016-06-22, 3d
        可行性报告     :after a1, 5d
        概念验证       : 5d
    section 项目实施
        概要设计      :2016-07-05  , 5d
        详细设计      :2016-07-08, 10d
        编码          :2016-07-15, 10d
        测试          :2016-07-22, 5d
    section 发布验收
        发布: 2d
        验收: 3d
```

### 7. 绘制表格

| 项目        | 价格   |  数量  |
| --------   | -----:  | :----:  |
| 计算机     | \$1600 |   5     |
| 手机        |   \$12   |   12   |
| 管线        |    \$1    |  234  |

### 8. 更详细语法说明

想要查看更详细的语法说明，可以参考我们准备的 [Cmd Markdown 简明语法手册][1]，进阶用户可以参考 [Cmd Markdown 高阶语法手册][2] 了解更多高级功能。

总而言之，不同于其它 *所见即所得* 的编辑器：你只需使用键盘专注于书写文本内容，就可以生成印刷级的排版格式，省却在键盘和工具栏之间来回切换，调整内容和格式的麻烦。**Markdown 在流畅的书写和印刷级的阅读体验之间找到了平衡。** 目前它已经成为世界上最大的技术分享网站 GitHub 和 技术问答网站 StackOverFlow 的御用书写格式。

---

## 什么是 Cmd Markdown

您可以使用很多工具书写 Markdown，但是 Cmd Markdown 是这个星球上我们已知的、最好的 Markdown 工具——没有之一 ：）因为深信文字的力量，所以我们和你一样，对流畅书写，分享思想和知识，以及阅读体验有极致的追求，我们把对于这些诉求的回应整合在 Cmd Markdown，并且一次，两次，三次，乃至无数次地提升这个工具的体验，最终将它演化成一个 **编辑/发布/阅读** Markdown 的在线平台——您可以在任何地方，任何系统/设备上管理这里的文字。

### 1. 实时同步预览

我们将 Cmd Markdown 的主界面一分为二，左边为**编辑区**，右边为**预览区**，在编辑区的操作会实时地渲染到预览区方便查看最终的版面效果，并且如果你在其中一个区拖动滚动条，我们有一个巧妙的算法把另一个区的滚动条同步到等价的位置，超酷！

### 2. 编辑工具栏

也许您还是一个 Markdown 语法的新手，在您完全熟悉它之前，我们在 **编辑区** 的顶部放置了一个如下图所示的工具栏，您可以使用鼠标在工具栏上调整格式，不过我们仍旧鼓励你使用键盘标记格式，提高书写的流畅度。

![tool-editor](https://www.zybuluo.com/static/img/toolbar-editor.png)

### 3. 编辑模式

完全心无旁骛的方式编辑文字：点击 **编辑工具栏** 最右侧的拉伸按钮或者按下 `Ctrl + M`，将 Cmd Markdown 切换到独立的编辑模式，这是一个极度简洁的写作环境，所有可能会引起分心的元素都已经被挪除，超清爽！

### 4. 实时的云端文稿

为了保障数据安全，Cmd Markdown 会将您每一次击键的内容保存至云端，同时在 **编辑工具栏** 的最右侧提示 `已保存` 的字样。无需担心浏览器崩溃，机器掉电或者地震，海啸——在编辑的过程中随时关闭浏览器或者机器，下一次回到 Cmd Markdown 的时候继续写作。

### 5. 离线模式

在网络环境不稳定的情况下记录文字一样很安全！在您写作的时候，如果电脑突然失去网络连接，Cmd Markdown 会智能切换至离线模式，将您后续键入的文字保存在本地，直到网络恢复再将他们传送至云端，即使在网络恢复前关闭浏览器或者电脑，一样没有问题，等到下次开启 Cmd Markdown 的时候，她会提醒您将离线保存的文字传送至云端。简而言之，我们尽最大的努力保障您文字的安全。

### 6. 管理工具栏

为了便于管理您的文稿，在 **预览区** 的顶部放置了如下所示的 **管理工具栏**：

![tool-manager](https://www.zybuluo.com/static/img/toolbar-manager.jpg)

通过管理工具栏可以：

<i class="icon-share"></i> 发布：将当前的文稿生成固定链接，在网络上发布，分享
<i class="icon-file"></i> 新建：开始撰写一篇新的文稿
<i class="icon-trash"></i> 删除：删除当前的文稿
<i class="icon-cloud"></i> 导出：将当前的文稿转化为 Markdown 文本或者 Html 格式，并导出到本地
<i class="icon-reorder"></i> 列表：所有新增和过往的文稿都可以在这里查看、操作
<i class="icon-pencil"></i> 模式：切换 普通/Vim/Emacs 编辑模式

### 7. 阅读工具栏

![tool-manager](https://www.zybuluo.com/static/img/toolbar-reader.jpg)

通过 **预览区** 右上角的 **阅读工具栏**，可以查看当前文稿的目录并增强阅读体验。

工具栏上的五个图标依次为：

<i class="icon-list"></i> 目录：快速导航当前文稿的目录结构以跳转到感兴趣的段落
<i class="icon-chevron-sign-left"></i> 视图：互换左边编辑区和右边预览区的位置
<i class="icon-adjust"></i> 主题：内置了黑白两种模式的主题，试试 **黑色主题**，超炫！
<i class="icon-desktop"></i> 阅读：心无旁骛的阅读模式提供超一流的阅读体验
<i class="icon-fullscreen"></i> 全屏：简洁，简洁，再简洁，一个完全沉浸式的写作和阅读环境

### 8. 阅读模式

在 **阅读工具栏** 点击 <i class="icon-desktop"></i> 或者按下 `Ctrl+Alt+M` 随即进入独立的阅读模式界面，我们在版面渲染上的每一个细节：字体，字号，行间距，前背景色都倾注了大量的时间，努力提升阅读的体验和品质。

### 9. 标签、分类和搜索

在编辑区任意行首位置输入以下格式的文字可以标签当前文档：

标签： 未分类

标签以后的文稿在【文件列表】（Ctrl+Alt+F）里会按照标签分类，用户可以同时使用键盘或者鼠标浏览查看，或者在【文件列表】的搜索文本框内搜索标题关键字过滤文稿，如下图所示：

![file-list](https://www.zybuluo.com/static/img/file-list.png)

### 10. 文稿发布和分享

在您使用 Cmd Markdown 记录，创作，整理，阅读文稿的同时，我们不仅希望它是一个有力的工具，更希望您的思想和知识通过这个平台，连同优质的阅读体验，将他们分享给有相同志趣的人，进而鼓励更多的人来到这里记录分享他们的思想和知识，尝试点击 <i class="icon-share"></i> (Ctrl+Alt+P) 发布这份文档给好友吧！

------

再一次感谢您花费时间阅读这份欢迎稿，点击 <i class="icon-file"></i> (Ctrl+Alt+N) 开始撰写新的文稿吧！祝您在这里记录、阅读、分享愉快！

作者 [@ghosert][3]     
2016 年 07月 07日    

[^LaTeX]: 支持 **LaTeX** 编辑显示支持，例如：$\sum_{i=1}^n a_i=0$， 访问 [MathJax][4] 参考更多使用方法。

[^code]: 代码高亮功能支持包括 Java, Python, JavaScript 在内的，**四十一**种主流编程语言。

[1]: https://www.zybuluo.com/mdeditor?url=https://www.zybuluo.com/static/editor/md-help.markdown
[2]: https://www.zybuluo.com/mdeditor?url=https://www.zybuluo.com/static/editor/md-help.markdown#cmd-markdown-高阶语法手册
[3]: http://weibo.com/ghosert
[4]: http://meta.math.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference




