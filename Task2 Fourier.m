%������Ҫת��Ϊ������ASCII��
str_ascii = input('Please enter the 8 bit ASCII you want to transform:','s');

%�������8λASCII��ת��Ϊ�˸��ֶ��ϵĺ���ֵ
str_array = zeros(1,8);
for i = 1:8
    str_array(i) = eval(str_ascii(i));
end

%��ʼ���������������������ź�signal��������������������
syms x T;
T = 8;
singal_func = @(x) str_array(1).*(x>=0 & x<1) + str_array(2).*(x>=1 & x<2) + str_array(3).*(x>=2 & x<3)+str_array(4).*(x>=3 & x<4)+str_array(5).*(x>=4 & x<5)+str_array(6).*(x>=5 & x<6)+str_array(7).*(x>=6 & x<7)+str_array(8).*(x>=7 & x<8);

harmonic = [1 2 4 8 16];
for j = 1:length(harmonic)
    k = harmonic(j);
    c =(integral(singal_func,0,T))*2/T;
    factor1 = zeros(1,k);      %�˴�������An������ϵ��������
    factor2 = zeros(1,k);      %�˴�������Bn������ϵ��������
    sin_func = sym(factor1);     %��sin���ֵĺ�����factor1һһ��Ӧ
    cos_func = sym(factor2);     %��cos���ֵĺ�����factor2һһ��Ӧ
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
    SIN = dot(factor1,sin_func);      %�����е�sin���ֺ�����ϵ������ۼ����
    COS = dot(factor2,cos_func);      %�����е�cos���ֺ�����ϵ������ۼ����
    Fuorier = c/2 + SIN + COS;        %������Ҷ������ϵ����ձ��ʽ
    fplot(singal_func,[0,8]);
    hold on;
    fplot(Fuorier,[0,8]);
    title('Harmonic=1 2 4 8 16 Fourier Seriers Imitation');
end