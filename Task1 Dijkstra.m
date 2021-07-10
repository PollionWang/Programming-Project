n=10;   %设置矩阵大小,行列数均为总点数的方阵
initialpoint=1;  %设置起始点
m=zeros(n);%定义n阶零矩阵
%设置矩阵中非零非无穷的值（路径值），并且按顺序将所有10个点分别标记为1-10的数
m(1,2)=8;m(1,3)=4;m(2,4)=2;m(2,5)=4;
m(2,6)=4;m(3,4)=1;m(3,5)=4;m(3,9)=7;
m(4,5)=2;m(5,6)=4;m(5,7)=2;m(6,8)=3;
m(7,9)=1;m(7,8)=1;m(9,10)=5;m(8,10)=8;
m = m +m'; %将矩阵的横纵索引对换的值（代表着同样的两个点之间不论从哪个点到另一个点的距离都是一样的）简化输入距离值
m(m==0)=inf; %将除开已经标记路径值的点（即不相通点标记为无穷指，表示不相连）

%由于距离组成的矩阵的对角线是序号点自己到自己的距离，将其距离设置为0
for i=1:n
    m(i,i)=0;
end

pointsolution(1:n)=0;pointsolution(initialpoint)=1;%已经求出最短路径的点为1，未求出的为0
mindistance(1:n)=0;%存放到各点的最短距离
lastpoints(1:n)=0;%存放各点最短路径的上一点标号

while sum(pointsolution)<n %判断每一点是否都已找到最短路径
    unsolvedpoints=find(pointsolution==0);%找到还未找到最短路径的点
    solvedpoints=find(pointsolution==1);%找出已找到最短路径的点,不加参数也可以直接返回所有非零元素的索引
    min=inf;
    for i=1:length(solvedpoints)
        for j=1:length(unsolvedpoints)
            possiblevalue=mindistance(solvedpoints(i))+m(solvedpoints(i),unsolvedpoints(j));  %比较已确定的点与其相邻未确定点的距离
            if(possiblevalue<min)
                min=possiblevalue;
                lastpoint=solvedpoints(i);
                newpoint=unsolvedpoints(j);
             %这里就是在不断比较每个点距离最近的点，并且存放最后的上一最短点的标号到lastpoints，直到所有10个点都确定
            end
        end
    end
    mindistance(newpoint)=min;
    pointsolution(newpoint)=1;
    lastpoints(newpoint)=lastpoint; %最小值时的与之连接点
end
%以上是Dijkstra算法的基本部分

%以下是路径回溯部分
%基本的想法是根据已经求出的每个点的最短路径点的数组（lastpoints），不断对前一个点回溯
%最短路径的规划可以从最近的上一个点开始考虑
%就比如说10号点上一个最短点是9，那么我们可以再用同样的方法回溯9号点，依次这样回溯就可以得到所有的最短路径的点
path=zeros(n);%路径矩阵
path(:,n)=1:n;
for i=2:n
    temp=lastpoints(i);
    for j=1:(n-1)
        path(i,n-j)=temp;
        if (temp==1)
            break;
        else
            temp=lastpoints(temp);
        end
    end
end
        
disp(mindistance)%展示每一个点的最短路径的距离值，序号一一对应
disp(path)%展示每一个点最短路径的路线，每一行都是对应的点的最短路径规划