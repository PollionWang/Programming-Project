%输入需要转化为方波的ASCII码
str_ascii = input('Please enter the 8 bit ASCII you want to transform:','s');

%将输入的8位ASCII码转化为八个分段上的函数值
str_array = zeros(1,8);
for i = 1:8
    str_array(i) = eval(str_ascii(i));
end

%开始着手设置匿名函数（即信号signal函数），并且申明周期
syms x T;
T = 8;
singal_func = @(x) str_array(1).*(x>=0 & x<1) + str_array(2).*(x>=1 & x<2) + str_array(3).*(x>=2 & x<3)+str_array(4).*(x>=3 & x<4)+str_array(5).*(x>=4 & x<5)+str_array(6).*(x>=5 & x<6)+str_array(7).*(x>=6 & x<7)+str_array(8).*(x>=7 & x<8);

harmonic = [1 2 4 8 16];
for j = 1:length(harmonic)
    k = harmonic(j);
    c =(integral(singal_func,0,T))*2/T;
    factor1 = zeros(1,k);      %此处构造存放An的所有系数的数组
    factor2 = zeros(1,k);      %此处构造存放Bn的所有系数的数组
    sin_func = sym(factor1);     %将sin部分的函数与factor1一一对应
    cos_func = sym(factor2);     %将cos部分的函数与factor2一一对应
    for n=1:k
        sin_part = @(x) (str_array(1).*(x>=0 & x<1) + str_array(2).*(x>=1 & x<2) + str_array(3).*(x>=2 & x<3) + str_array(4).*(x>=3 & x<4) + str_array(5).*(x>=4 & x<5) + str_array(6).*(x>=5 & x<6) + str_array(7).*(x>=6 & x<7) + str_array(8).*(x>=7 & x<8)).*sin(2*pi*n*x/T);
        cos_part = @(x) (str_array(1).*(x>=0 & x<1) + str_array(2).*(x>=1 & x<2) + str_array(3).*(x>=2 & x<3) + str_array(4).*(x>=3 & x<4) + str_array(5).*(x>=4 & x<5) + str_array(6).*(x>=5 & x<6) + str_array(7).*(x>=6 & x<7) + str_array(8).*(x>=7 & x<8)).*cos(2*pi*n*x/T);
        An =(integral(sin_part,0,T))*2/T;
        factor1(n) = An;
        Bn =(integral(cos_part,0,T))*2/T; 
        factor2(n) = Bn;
        sin_func(n)= sin(2*pi*n*x/T);
        cos_func(n)= cos(2*pi*n*x/T);
    end
    SIN = dot(factor1,sin_func);      %将所有的sin部分函数与系数相乘累加求和
    COS = dot(factor2,cos_func);      %将所有的cos部分函数与系数相乘累加求和
    Fuorier = c/2 + SIN + COS;        %即傅里叶级数拟合的最终表达式
    fplot(singal_func,[0,8]);
    hold on;
    fplot(Fuorier,[0,8]);
    title('Harmonic=1 2 4 8 16 Fourier Seriers Imitation');
end