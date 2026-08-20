# xv6-labs-2025

这是我的 MIT 6.1810 2025 xv6 操作系统课程实验仓库，用于保存九个 Lab 的实现、测试结果与课程设计报告。项目以 RISC-V 版本 xv6 为基础，内容覆盖用户程序、系统调用、虚拟内存、陷阱、网络驱动、并发控制、文件系统和内存映射。

当前 `report` 分支只保存最终报告及其图片素材，实验源码分别保存在对应的 Lab 分支中，避免报告文件与各实验版本的源码混在一起。

> 本仓库用于课程学习和实验记录。不同年份的 xv6 Lab 内容与测试可能不同，请以 [MIT 6.1810 2025](https://pdos.csail.mit.edu/6.828/2025/) 官方页面为准。

## 完成情况

| Lab | 主要内容 | 分支 | 最终评分 |
| --- | --- | --- | ---: |
| Unix utilities | `sleep`、`sixfive`、`memdump`、`find -exec` | [`util`](https://github.com/lbyy718/xv6-labs-2025/tree/util) | 131/131 |
| System calls | GDB、sandbox、路径例外、内存残留攻击 | [`syscall`](https://github.com/lbyy718/xv6-labs-2025/tree/syscall) | 45/45 |
| Page tables | 页表分析、USYSCALL、页表打印、超级页 | [`pgtbl`](https://github.com/lbyy718/xv6-labs-2025/tree/pgtbl) | 41/41 |
| Traps | RISC-V 汇编、Backtrace、Alarm | [`traps`](https://github.com/lbyy718/xv6-labs-2025/tree/traps) | 95/95 |
| Copy-on-write | COW fork、写缺页、引用计数 | [`cow`](https://github.com/lbyy718/xv6-labs-2025/tree/cow) | 130/130 |
| Network driver | E1000 网卡驱动、UDP Receive | [`net`](https://github.com/lbyy718/xv6-labs-2025/tree/net) | 171/171 |
| Locking | 每 CPU 空闲链表、写者优先读写锁 | [`lock`](https://github.com/lbyy718/xv6-labs-2025/tree/lock) | 100/100 |
| File system | 二级间接块、符号链接 | [`fs`](https://github.com/lbyy718/xv6-labs-2025/tree/fs) | 100/100 |
| Memory mapping | `mmap`、`munmap`、惰性装页与共享写回 | [`mmap`](https://github.com/lbyy718/xv6-labs-2025/tree/mmap) | 170/170 |

## 查看实验源码

克隆仓库并查看所有实验分支：

```bash
git clone https://github.com/lbyy718/xv6-labs-2025.git
cd xv6-labs-2025
git branch --all
```

切换到需要查看的实验分支，例如 Traps：

```bash
git switch traps
```

安装 RISC-V 交叉编译工具链和 QEMU 后，可在实验分支编译并启动 xv6：

```bash
make qemu
```

进入 xv6 shell 后可运行当前实验对应的用户程序。退出 QEMU 时先按 `Ctrl+A`，再按 `X`。

运行该分支的完整评分：

```bash
make clean
make grade
```

部分 Lab 也提供专项评分命令。例如：

```bash
./grade-lab-traps alarm
./grade-lab-fs symlinktest
./grade-lab-mmap mmaptest
```

专项脚本只存在于对应 Lab 分支，运行前应先切换到正确分支。`report` 分支不包含 xv6 源码，不能在本分支运行 `make qemu` 或 `make grade`。

## 报告

- [课程设计报告 Markdown](xv6课程设计报告.md)
- [课程设计报告 PDF](xv6课程设计报告.pdf)
- [报告使用的实验截图](report-assets/)

报告包括环境搭建、每个实验的目的与要求、实现过程、测试结果、遇到的问题及解决方法、实验心得和综合分析。

## report 分支结构

```text
README.md              仓库说明
xv6课程设计报告.md     报告 Markdown 源文件
xv6课程设计报告.pdf    最终 PDF 报告
report-assets/         报告中的实验截图
LICENSE                xv6 项目许可证
```

## 参考资料

- [MIT 6.1810 Fall 2025](https://pdos.csail.mit.edu/6.828/2025/)
- [MIT xv6 Labs 2025](https://pdos.csail.mit.edu/6.828/2025/labs/)
- [xv6: a simple, Unix-like teaching operating system](https://pdos.csail.mit.edu/6.1810/2025/xv6/book-riscv-rev5.pdf)

本项目基于 MIT 教学操作系统 xv6。原始项目的版权与许可信息见 [LICENSE](LICENSE)。
