# GNCDB Shell

GNCDB Shell 是一个基于 SQLite 的命令行数据库管理工具，提供了数据库操作命令和用户界面。

## 项目特点

- 支持标准的 SQL 语句执行
- 提供丰富的点命令（dot commands）支持
- 支持多种输出格式（CSV、Excel等）
- 内置帮助系统
- 支持数据库备份和恢复
- 支持数据库导入导出
- 支持数据库配置管理

## 主要功能

### 数据库操作

- 数据库连接和断开
- 数据库备份和恢复
- 数据库克隆
- 数据库导入导出

### 查询和显示

- SQL 查询执行
- 多种输出格式支持
- 结果集格式化
- 表结构查看

### 系统命令

- 工作目录切换
- 日志管理
- 配置管理
- 帮助系统

## 项目结构

```
.
├── src/                # 源代码目录
│   ├── main.c         # 主程序入口
│   ├── callback.c     # SQL 回调函数实现
│   ├── utils.c        # 工具函数实现
│   ├── help.c         # 帮助系统实现
│   ├── callback.h     # 回调函数声明
│   ├── util.h         # 工具函数声明
│   └── help.h         # 帮助系统声明
├── gncdblib/          # 库文件目录
├── log/               # 日志目录
├── makefile          # 构建脚本
└── config.ini        # 配置文件
```

## 构建和运行

1. 确保已安装必要的编译工具
2. 执行 `make` 命令进行编译
3. 运行生成的可执行文件

## 使用说明

1. 启动程序后，可以输入 SQL 语句或点命令
2. 使用 `.help` 命令查看所有可用命令
3. 使用 `.help 命令名` 查看具体命令的使用说明

## 示例

```sql
-- 创建表
CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);

-- 插入数据
INSERT INTO users (name, age) VALUES ('张三', 25);

-- 查询数据
SELECT * FROM users;

-- 使用点命令
.help
.mode csv
.output result.csv
```

## 注意事项

- 请确保有足够的磁盘空间进行数据库操作
- 重要操作前建议先备份数据
- 注意数据库文件的访问权限

## 贡献指南

欢迎提交 Issue 和 Pull Request 来帮助改进项目。

## 安装信息

### 包信息
- 包名：`gncdb-shell`
- 版本：1.0.0
- 维护者：Zyy <zyye9135@mail.nwpu.edu.cn>

### 安装位置
- 可执行文件：`/usr/bin/gncdb_shell`
- 文档：`/usr/share/doc/gncdb-shell`
- 配置文件：`/etc/gncdb-shell/config.ini`
- 日志目录：`/var/log/gncdb-shell`

### 依赖项
- libreadline8

## 使用方法

### 运行程序
在终端中直接输入：
```bash
gncdb_shell
```

### 查看安装信息
查看已安装的文件：
```bash
dpkg -L gncdb-shell
```

查看包的详细信息：
```bash
dpkg -s gncdb-shell
```

### 卸载程序
```bash
sudo dpkg -r gncdb-shell
```

## 从源码构建

### 构建步骤
```bash
mkdir build
cd build
cmake ..
make
```

### 打包
```bash
cpack
```

### 安装生成的包
```bash
sudo dpkg -i gncdb-shell-1.0.0-Linux.deb
```
