Conway's Game of Life 模式
这份文档描述了在 Conway's Game of Life 中实现的一些常见模式。每个模式都是由一组活细胞组成的，这些细胞在游戏的每一轮中都会根据一组规则生存、死亡或生成。

Bee-hive
Bee-hive 是一个稳定的模式，由6个细胞组成。它需要一个至少3x3的网格来容纳。

Beacon
Beacon 是一个周期为2的振荡器，由8个细胞组成。它需要一个至少4x4的网格来容纳。

Glider
Glider 是一个周期为4的飞行器，由5个细胞组成。它需要一个至少3x3的网格来容纳。

Block
Block 是一个稳定的模式，由4个细胞组成。它需要一个至少2x2的网格来容纳。

Loaf
Loaf 是一个稳定的模式，由7个细胞组成。它需要一个至少4x4的网格来容纳。

Boat
Boat 是一个稳定的模式，由5个细胞组成。它需要一个至少3x3的网格来容纳。

Tub
Tub 是一个稳定的模式，由4个细胞组成。它需要一个至少3x3的网格来容纳。

Blinker
Blinker 是一个周期为2的振荡器，由3个细胞组成。它需要一个至少3x1的网格来容纳。

Toad
Toad 是一个周期为2的振荡器，由6个细胞组成。它需要一个至少4x2的网格来容纳。

Pulsar
Pulsar 是一个周期为3的振荡器，由48个细胞组成。它需要一个至少13x13的网格来容纳。

Pentadecathlon
Pentadecathlon 是一个周期为15的振荡器，由10个细胞组成。它需要一个至少8x3的网格来容纳。

Lightweight Spaceship
Lightweight Spaceship 是一个周期为4的飞行器，由9个细胞组成。它需要一个至少5x4的网格来容纳。

Middleweight Spaceship
Middleweight Spaceship 是一个周期为4的飞行器，由11个细胞组成。它需要一个至少6x5的网格来容纳。

Heavyweight Spaceship
Heavyweight Spaceship 是一个周期为4的飞行器，由14个细胞组成。它需要一个至少7x5的网格来容纳。

每个模式都是在网格的中心位置生成的。如果网格的大小不足以容纳特定的模式，程序将打印一条错误消息并返回。

用户输入
用户需要在命令行中提供一个模式名称作为参数来运行程序。例如，如果用户想要初始化一个 Lightweight Spaceship 模式，他们可以运行以下命令：

./game_of_life LightweightSpaceship

在程序运行期间，用户可以按 's' 键来保存当前的世界状态到一个 BMP 文件中。例如，如果用户在运行程序后按 's' 键，程序将会保存当前的世界状态到一个名为 "game_of_life.bmp" 的文件中。