# DJI Onboard SDK (OSDK) 3.8.1

[![Join the chat at https://gitter.im/dji-sdk/Onboard-SDK](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/dji-sdk/Onboard-SDK?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## What is the DJI Onboard SDK?

The DJI Onboard SDK allows you to connect your own Onboard Computer to a [supported](https://developer.dji.com/onboard-sdk/documentation/introduction/osdk-hardware-introduction.html#supported-products) DJI vehicle or flight controller using a serial port (TTL UART). For full documentation, please visit the [DJI Developer Site](https://developer.dji.com/onboard-sdk/documentation/). Documentation regarding the code can be found in the [OSDK API Reference](https://developer.dji.com/onboard-api-reference/index.html) section of the developer website.

## Latest Release
OSDK 3.8.1 was released on 4 June 2019. This release adds support of Onboard-Payload SDK communication and Z30 zooming API for M210 series V2. Additionally, bugfixes for camera video support issues and STM32 platform issues are also added in this release. Please see the [release notes](https://developer.dji.com/onboard-sdk/documentation/appendix/releaseNotes.html) for more information.


## Last Major Release
OSDK 3.8 was released on 4 April 2019. This release adds support of M210 V2, new time synchronization feature, and waypoint mission v2 (beta). Please see the [release notes](https://developer.dji.com/onboard-sdk/documentation/appendix/releaseNotes.html) for more information.
## Firmware Compatibility

This chart shows the latest firmware that were available and are supported at the time of 3.8.1 release.

| Aircraft/FC           | Firmware Package Version | Flight Controller Version | OSDK Branch            | Notes                                                                 |
|-----------------------|--------------------------|---------------------------|------------------------|-----------------------------------------------------------------------|
| **M210/M210 RTK V2**  | **1.0.0450**             | **3.4.3.31**              | **OSDK 3.8.1**         |                                                                       |
|                       |                          |                           |                        |                                                                       |
| **M210/M210 RTK**     | **1.2.0440**             | **3.3.10.12**             | **OSDK 3.8.1**         |                                                                       |
|                       |                          |                           |                        |                                                                       |
| **M600/M600 Pro**     | **1.0.1.66**             | **3.2.41.13**             | **OSDK 3.8.1**         |                                                                       |
|                       |                          |                           |                        |                                                                       |
| **A3/A3 Pro**         | **1.7.6.0**              | **3.3.8.39**              | **OSDK 3.8.1**         |                                                                       |
|                       |                          |                           |                        |                                                                       |
| **N3**                | **1.7.6.0**              | **3.3.8.39**              | **OSDK 3.8.1**         |                                                                       |
|                       |                          |                           |                        |                                                                       |
| **M100**              | 1.3.1.82                 | **3.1.10.0**              | **OSDK 3.8.1**         |                                                                       |


## Support

You can get support from DJI and the community with the following methods:

- **Send email to dev@dji.com** describing your problem and a clear description of your setup
- Github Issues or [gitter.im](https://gitter.im/dji-sdk/Onboard-SDK)
- Post questions on [**Stackoverflow**](http://stackoverflow.com) using [**dji-sdk**](http://stackoverflow.com/questions/tagged/dji-sdk) tag
- [**DJI Forum**](http://forum.dev.dji.com/en)

# 以下为个人修改内容

## 定位思路

1. **定高思路**：室内纯气压定高的话，因为室内的气压不是很稳定，特别是在飞机飞行的过程中，桨叶的风容易干扰到气压计，导致数据突变，出现飞行高度不稳定的现象。GUIDANCE是采用双目加超声波的方法实现的，我们这里采用的是激光，也可以使用市面上的其他的高度传感器。读取激光的高度，油门回中的时候记住此时激光高度。然后使用PID进行闭环控制，将最终的结果控制飞机的垂直速度（使用SDK中的垂直速度控制API）。为了避免飞机飞过一些不平坦的地方，飞行高度变化太过于剧烈，可以使用激光高度的变化率，当变化过大时，削弱激光修正高度的系数，并且当重新稳定的时候再次确定高度。

2. **定点思路**：从光流模块中，可以得到光流的速度数据，可以通过定时器计算前后二次数据的时间间隔，然后将速度进行积分，得到距离，再将速度以及距离进行闭环控制，将最终的结果当飞机的目标角度传入API中。另外，在飞行过程中关掉光流的作用，当遥控杆子回中的时候，把目标速度变为0，此时不要外环位置环的作用，可以达到刹车稳定的目标。当刹车后速度在一个小范围内，就重新加入位置环，并且把目前的位置当为目标位置。

注意：不一定要使用光流，也可以试试其他方法。例如沈老师的vins开源算法+Realsense+manifold2. 
网址  https://zhuanlan.zhihu.com/p/59646674

## SDK开发注意事项

1. STM32的板子初始化后要先等待一段时间，可以在初始化中加延时，或者等飞控成功启动再给板子上电，否则通讯会不成功。
2. 之前出现过飞控的控制权被抢回去，自己还不知道，所以大家需要给飞机装个灯或者其他东西，进入SDK模式的时候，可以通过亮灯的形式来提醒飞手。同样需要写一个功能，就是可以通过掰动遥控杆子进入或退出SDK模式，当自己写的东西出错的时候，遥控可以立马夺回板子的控制权。
3. 在给飞控增加新功能时，要注意一定要在模拟器中先验证一下，不能直接拿飞机飞行验证。（在模拟器中，如果不进入SDK模式，是默认GPS定位的。比如自己写了光流定位的代码，可以掰动摇杆进入SDK模式，此时因为飞机的定位信息来自光流模块的信息，而不是模拟器中虚拟的GPS信息，所以模拟器中的飞机会慢慢飘走，并且飞行过程不会刹车。你可以手动移动一下真实的飞机，那么此时光流就会有移动的数据，模拟器中的飞机就会朝你移动的反方向一直移动，当你把真实的飞机移动回原来的位置，那么虚拟器中的飞机就会停下来，这样说明定位思路是正确的，才可以拿出去外面试试。定高修正的思路也是一样的，目标高度确定了，当你拿起真实飞机的时候，模拟器中的飞机肯定是一直下降，除非你回到之前的位置，它才会停下来）
4. 建议大家可以先用小一点的飞机调试（f330或者f450），等调试稳定才再上大飞机，大四轴有点危险，调试还是命要紧，同样钱也重要，所以买小的来玩玩。
5. 无论是想在飞机上开发什么功能，要先在DJI Assistant2软件上把飞控原本的参数调试到最佳，不然其他就白做了，本人原先在f450上做好定位功能，整套拆下来装到大四轴的时候，大四轴飞起来软绵绵的。并且大四轴重量变化较大时，飞控原本的参数也就没用了，所以大家要调好参数（基础感度，动力带宽，姿态感度，具体可以参考 https://www.iqiyi.com/v_19rrari2fo.html ），使得飞机在定高模式飞行时姿态平稳，没有抖动，原先就是没有注意这个问题，以为是定位问题，浪费了很多时间。
6. 使用API的时候，要注意API可以根据自己的需求改动，原先的API是当你想控制飞机的姿态角度的时候，那么垂直方向只能控制高度。当你想控制垂直方向的速度时，那么姿态角就只能控制角速度，因为垂直方向用高度信息还有YAW用角度控制的话，飞行效果不是很好，有点迟钝，想用速度控制二个API就矛盾了(可以从模拟器中看出)，写了很多代码才实现，后面发现可以直接改API，方便了很多，我把PITCH，ROLL改成角度控制，而YAW以及高度采用角速度和速度控制（图十），飞起来就比较顺手，反应比之前灵敏（也可能是我自己不会用，我感觉原先的API应该是给自动飞行设计的）。
7. 光流的安装方式也会影响到飞行效果，一般的光流都是需要装在飞机的正下方，如果没有装正下方的话需要自己去修正，如果用匿名光流的话，需要你自己细看一下手册，直接在上位机上设置就可以了。（匿名光流可以在淘宝购买，店家就是匿名科创）
8. 大四轴飞行的时候，如果是在室内，飞行的高度要高一些，因为会有地效的作用，太低飞机会晃动，调试飞机参数的时候，尽量高一些，并且飞机起飞的环境不要太过于密闭。
9. A3等其他飞控同样支持SDK二次开发，建议可以试试A3,毕竟价格高，优势肯定也是有的。

## 代码文件

|文件名|功能|
|-|-|
|Driver.cpp|板子初始化，并且判断时间执行对应任务|
|Led.cpp   buzzer.cpp|主要用来提醒自己进入SDK模式，自己用了蜂鸣器，比赛建议使用灯比较明显，因为四轴噪声太大|
|Time.cpp|原先大疆例程的系统时钟以及定时器初始化|
|Control.cpp|主要是定位还有发送位置控制指令|
|Communication.cpp|初始化串口，用来与N3飞控以及电脑上位机通讯|
|Sub_information.cpp|用来订阅相关信息|
|Pid.cpp|pid实现的函数，建议大家有空可以试试自抗干扰（ADRC），不过任何改动可以在模拟器还有小飞机试试|
|Optical_flow.cpp|光流数据接收分析代码，根据买的光流协议编写|

## 代码运行流程

该代码在STM32F4上面运行，这个例程代码默认使用正点原子的匿名光流模块，该工程文件运行流程如下所示：

1. **填写ID和Key**：首先在User/Activate.cpp文件中填写ID和key，这个数据请到大疆开发者网站上面，注册应用，之后就可以拿到上面两串字符，复制粘贴过来即可。
2. **拿到控制权限**：main函数文件中，等待N3飞控启动需要延时（默认30000ms），之后初始化串口，打印出示例说明，检查固件版本与OSDK版本是否一致。之后拿到控制权限后进入loop循环中。
3. **信息订阅函数**：Loop循环进入Driver/driver.cpp函数中，该函数根据时间戳与当前时间的差值确定不同的频率调用哪些控制函数。我们此时设置四种不同的频率并多线程运行四个函数：250HZ为控制指令频率（即控制飞机的指令，频率最高），100HZ为位置计算频率（根据光流的数据计算位置偏差），50HZ为订阅飞控信息频率（该频率要与DJI Assistant上位机设置的频率一致），最后一个是控制模式切换频率，该频率为1HZ，较低，必要时从SDK模式切回手动控制模式，用于防无人机抽风（hhhhhhhh）。
4. **控制指令函数**：该函数位于Driver/control.cpp文件中。首先判断用遥控摇杆开启或者关闭onboard sdk模式，注意要夺回控制权或者放弃控制权，方便飞机出问题可以用遥控器退出开发者模式，并将光流距离清除。之后的一个判断函数，判断飞机是否起飞，飞机没有起飞前把当前激光或者超声波高度数据记为目标高度(飞行过程中实际上靠飞机上的气压计，第三方测距只是防止飞机室内飞行)。之后的一个判断函数，判断动油门遥感后要重新确定第三方测距模块目标高度，方便飞行维持高度稳定。动油门回中一段时间后再记下目标高度，先让飞机垂直方向上的速度降低，不然立马确认高度反应可能有点剧烈。下一个函数是判断无人机控制情况，控制无人机位置，可以看下控制位置以及高度的API，可以根据自己的需求去修改API，不动方向遥感，只动油门的时候，水平位置使用光流数据进行闭环控制，不动油门，只动方向遥感的时候，用激光或者超声波进行垂直方向的速度控制。最后，注意光流最终输出的角度要限制好幅度，包括api其他的角度控制。
5. **位置计算函数**：该函数位于Driver/control.cpp文件中。该函数首先记录了上一次遥控器的pitch和roll值，在sdk模式中，遥控不在中间的时候，需要置相关标志位，关掉对应轴向的位置控制，回中时，使用光流数据进行刹车。在处于定位模式下时 Flow.DETERMINED == true 说明已经确定激光目标高度。此时飞行过程中，==有可能经过一些不平的地方或者小车从下面经过，导致激光数据突变==，如果变化超过一定范围（10cm），削弱激光修正高度的比例,不然飞机高度容易不稳定（激光修正的比例系数不能为0，室内气压定高不好）。较长时间下方有车子移动，或者经常在不平的地面飞行，那么飞机因为激光修正的削弱，短时间不会出现掉高现象，当垂直的速度稳定一段时间，重新确定当前激光高度为目标高度，并且加大激光修正 ，这样可以防止车子停飞机下端或者飞机飞到一些与当前位置高度不同的地方出现高度变化严重现象。高度环，水平位置环采用50HZ执行频率，水平位置的速度环使用100HZ。改变高度的时候，可以把光流的参数改小点，等高度确定再恢复，因为飞机高度变化，会引起光流数据变化 此处没加，需要的可以自己加。油门回中并且目标高度确定，用PID输出控制飞机的垂直方向速度，防止飞机掉高严重。方向杆回中的时候，此时用光流的数据进行刹车并且悬停 ，先让飞机停下来，所以把目标速度设置为0，当飞机水平位置移动变慢时，确定一段时间内速度变慢。这时就可以把当前位置记为目标位置。
==注意==：通过灯是否闪烁判断此时飞控处于onboard sdk模式还是遥控模式（此处用的是蜂鸣器，比赛建议用比较显眼的灯，方便飞行手判断此时是否处于sdk模式）。判断飞机的状态，一定要注意不在sdk模式要释放控制权，防止自己写的东西出问题，与N3飞控通讯失败，没释放控制权会导致飞机按照你最后发的指令一直执行，导致后面其他不可描述的事情发生。
6. **订阅飞控信息函数**：该函数位于Driver/control.cpp文件中。该函数订阅了遥控器数据，绝对高度融合数据，气压计高度数据，融合高度数据，四元数信息，飞行状态，控制设备模式（sdk or 手动），并调用匿名光流模块的数据。
7. **控制模式切换函数**：该函数位于Driver/control.cpp文件中。该函数通过灯是否闪烁判断此时飞控处于onboard sdk模式还是遥控模式（此处用的是蜂鸣器，比赛建议用比较显眼的灯，方便飞行手判断此时是否处于sdk模式）。注意：SDKInfo结构体位于osdk-core/api/inc/dji_telemetry.hpp文件中（STM32与linux，ROS共享API头文件），deviceStatus变量为0的时候是遥控模式，1为app控制，2为串口控制。flightStatus变量为0的时候是关闭，1为opensd模式。判断飞机的状态，一定要注意不在sdk模式要释放控制权，防止自己写的东西出问题，与N3飞控通讯失败，没释放控制权会导致飞机按照你最后发的指令一直执行，导致后面其他不可描述的事情发生。
