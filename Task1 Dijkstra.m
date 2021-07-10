n=10;   %���þ����С,��������Ϊ�ܵ����ķ���
initialpoint=1;  %������ʼ��
m=zeros(n);%����n�������
%���þ����з���������ֵ��·��ֵ�������Ұ�˳������10����ֱ���Ϊ1-10����
m(1,2)=8;m(1,3)=4;m(2,4)=2;m(2,5)=4;
m(2,6)=4;m(3,4)=1;m(3,5)=4;m(3,9)=7;
m(4,5)=2;m(5,6)=4;m(5,7)=2;m(6,8)=3;
m(7,9)=1;m(7,8)=1;m(9,10)=5;m(8,10)=8;
m = m +m'; %������ĺ��������Ի���ֵ��������ͬ����������֮�䲻�۴��ĸ��㵽��һ����ľ��붼��һ���ģ����������ֵ
m(m==0)=inf; %�������Ѿ����·��ֵ�ĵ㣨������ͨ����Ϊ����ָ����ʾ��������

%���ھ�����ɵľ���ĶԽ�������ŵ��Լ����Լ��ľ��룬�����������Ϊ0
for i=1:n
    m(i,i)=0;
end

pointsolution(1:n)=0;pointsolution(initialpoint)=1;%�Ѿ�������·���ĵ�Ϊ1��δ�����Ϊ0
mindistance(1:n)=0;%��ŵ��������̾���
lastpoints(1:n)=0;%��Ÿ������·������һ����

while sum(pointsolution)<n %�ж�ÿһ���Ƿ����ҵ����·��
    unsolvedpoints=find(pointsolution==0);%�ҵ���δ�ҵ����·���ĵ�
    solvedpoints=find(pointsolution==1);%�ҳ����ҵ����·���ĵ�,���Ӳ���Ҳ����ֱ�ӷ������з���Ԫ�ص�����
    min=inf;
    for i=1:length(solvedpoints)
        for j=1:length(unsolvedpoints)
            possiblevalue=mindistance(solvedpoints(i))+m(solvedpoints(i),unsolvedpoints(j));  %�Ƚ���ȷ���ĵ���������δȷ����ľ���
            if(possiblevalue<min)
                min=possiblevalue;
                lastpoint=solvedpoints(i);
                newpoint=unsolvedpoints(j);
             %��������ڲ��ϱȽ�ÿ�����������ĵ㣬���Ҵ��������һ��̵�ı�ŵ�lastpoints��ֱ������10���㶼ȷ��
            end
        end
    end
    mindistance(newpoint)=min;
    pointsolution(newpoint)=1;
    lastpoints(newpoint)=lastpoint; %��Сֵʱ����֮���ӵ�
end
%������Dijkstra�㷨�Ļ�������

%������·�����ݲ���
%�������뷨�Ǹ����Ѿ������ÿ��������·��������飨lastpoints�������϶�ǰһ�������
%���·���Ĺ滮���Դ��������һ���㿪ʼ����
%�ͱ���˵10�ŵ���һ����̵���9����ô���ǿ�������ͬ���ķ�������9�ŵ㣬�����������ݾͿ��Եõ����е����·���ĵ�
path=zeros(n);%·������
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
        
disp(mindistance)%չʾÿһ��������·���ľ���ֵ�����һһ��Ӧ
disp(path)%չʾÿһ�������·����·�ߣ�ÿһ�ж��Ƕ�Ӧ�ĵ�����·���滮