# AIsnake

## 项目背景
这是上海交通大学软件学院软件基础实践(大二上学期)的课前project。
要求是用QT完成一个能支持随机地形，多人对战，AI寻路等功能的贪吃蛇。
具体要求如下
在本项⽬中，你将独⾃实现⼀个贪吃蛇游戏，具体内容包括：
1. 编程环境的搭建(5%)
2. 基本功能(35%)
1. 蛇的显示和移动
2. 墙和⻝物的显示与判定
3. 进阶功能(30%)
1. 单机多⼈游戏(多条蛇，不同按键控制不同蛇)
2. 具有特殊效果的⻝物(具体效果请发挥你的想象⼒)
3. 初始地形以及随机产⽣的砖块
4. 简单的AI蛇(策略⾃拟，如按照最短路径去吃最近的⻝物等，⽆需实现的⾮常复杂)
4. 其他功能(10%)
1. 除上述功能外，增加⾄少⼀项其他功能
5. ⾯向对象的设计、注释以及代码⻛格(20%)

## 项目设计

* 蛇，食物，砖块的设计
![snake architecture](example/arch_snake.PNG)

* 自定义风格的设计
![style architecture](example/arch_style.PNG)

* 游戏逻辑与用户操作的设计
![board architecture](example/arch_board.PNG)

## 项目创意
> * bfs在智能蛇实现中的应用
> * 双人PK时，引入蛇可以互相捕获的玩法，即蛇在咬到其他蛇的蛇身后，能够将其他蛇的蛇身以一定比例消化为自身的。这样使得双人PK时不仅需要考虑食物，地形，还要与对方展开搏斗，增加趣味性。
> * 产生具有特殊效果的食物——带有隐身buff的食物，这在双人PK时非常有用，隐身数个时间周期后，玩家可以出其不意的攻击对方蛇身，让对方措手不及。
> * 多种自定义风格的实现，每一种风格都会有相应的按钮，背景，底色。同样，蛇身与砖块也会根据不同风格呈现不一样的变化。

## 项目总结
>这个项目是我分为两次完成的，第一次是在学期中间，因为学期末有一次checkpoint,我于是花了大概三天时间，熟悉qt和写一个最原始的贪吃蛇，只支持贪吃蛇的基本功能（移动，换方向，吃食物，判断死亡）。在暑假中间，花了大概有五天的时间在第一次的基础上重构。

>在这个项目中运用到了之前一些课程学习的知识：如c++程序设计(对c++的使用)，数据结构(bfs的应用)，软件工程(项目结构的设计)。


## 项目展示
最后的成品图如下：

* 首页
![首页](/example/homepage.png)

* 游戏页面(人机对战)
![游戏页面](/example/gameplayaipk.png)

    这个项目支持用户选择不同的主题，上面的图片来自于sea style,还可选择的主题有forest,prairie,window,fusion：

* 游戏页面(双人PK,prairie style)
![游戏页面](/example/gameplaydoubleplayers.png)

* 游戏页面(ai)
![](/example/aiplay.png)