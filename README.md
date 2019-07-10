# f5529框架
system_init.h中包括了其他所有的.h文件
这个框架使用的是f5529lp开发的使用的是iar为了方便所以只上传了.c .h下载后自行添加到项目中
其中cog12864采用的是艾研信息的拓展板可以用oled替换，oled没有字库所以asciifonts.h"//ASCII表、"chinesefonts.h"//中文字符是使用字模软件直接生成的。
只需要将使用的字模替换就行，注释中有替换所需设置。


 PrintString(uchar col,uchar page,uchar *ch)函数使用方法：
 将字模软件的数组替换到chinesefonts.h中每个字编号
 main中开一个字符数组
 例：
 unsigned char disp0[]={0x80+0,0x80+1,0x80+2,0x80+3,0x80+4,0};
unsigned char disp1[]={0x80+5,0x80+6,0x80+7,0x80+8,0x80+9,':',0};
unsigned char disp2[]={0x80+10,0x80+11,0x80+12,0x80+13,':',0};
unsigned char disp3[]={0x80+14,0x80+15,0x80+16,':',0};

加上0x80表示汉字，不是汉字则不用加，每行一0结尾哦
再在需要显示的地方加上函数：
  PrintString(3\*8,0,disp0);
  PrintString(0\*8,2,disp1);
  PrintString(0\*8,4,disp2);
  PrintString(0\*8,6,disp3);
  因为8个col表示一个汉字，起始col为第三个汉字的位置，起始page为第一行所以为0。
  非汉字则所有字模都在asciifonts.h，去掉0x80其他使用方法一样。
  
  
  print_number(uchar col,uchar page,unsigned int a)函数使用方法：
  例：
  print_number(11\*8,2,DHT11T_Data_H);
  col、page和上面一样，最后一个参数直接输入变量或常量即可
  
  关于system_init
  直接在main.c中调用system_init();即可
  dht11模块在while（1）或其他地方直接调用dht11();即可，例程中添加了串口发送方法，若不需要去掉即可
  dht11的数据存放在DHT11T_Data_H, DHT11T_Data_L, DHT11RH_Data_H, DHT11RH_Data_L中，H为小数点前，L为小数点后
  
  
  关于UART
  采用异步通信方式，UCA1BR0 = 0x41; // 
  UCA1BR1 = 0x03; // 
  UCA1MCTL = 0x00; // 8MHz 9600 modulation
  可以通过430波特率计算工具算出寄存器配置的值更改（所选择时钟要确定，这里使用的8M smclk）
  本框架采用的9600
  
  关于clock
  //DCO频率范围在28.2MHZ以下//D=16，N=1//n=8,FLLREFCLK时钟源为XT2CLK；
  //DCOCLK=D\*(N+1)\*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
  //ACLK的时钟源为DCOCLKDIV,MCLK\SMCLK的时钟源为DCOCLK
  //ACLK由DCOCLKDIV的32分频得到，SMCLK由DCOCLK的2分频得到
  //最终MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
  可能这是我的时钟可以通过分频倍频获取各种频率，其他模块也可以更改时钟源
  
  关于timer
  TimerA更改ccr1和if或更改时钟源可以更改计数器的时间
  
  关于其他
  本次只写了这些模块后续更新adc12捕获中断和其他传感器的使用吧，程序中的备注因为修改了很多次所以有些不符合程序
  一切都以readme中为准，之后更新会吧用的字模软件和波特率计算工具一同上传
  
  
