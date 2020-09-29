clc;
close all;
clear all;

%�����ֵ��ȥ����������ƫ�����㷽��
wave_data=csvread('D:\STM32Project\matlab\GetQRMean.csv');
%��ȡǰ1000��ֵ
wave_data=wave_data(1:1000,:);
%����ḡ����
wave_data(:,1)=4*wave_data(:,1)/32767;
wave_data(:,2)=4*wave_data(:,2)/32767;
wave_data(:,3)=4*wave_data(:,3)/32767;
wave_data(:,4)=2000*wave_data(:,4)/32767;
wave_data(:,5)=2000*wave_data(:,5)/32767;
wave_data(:,6)=2000*wave_data(:,6)/32767;
wave_data(:,7)=wave_data(:,7)*((114-128)*0.5/128)+1;
wave_data(:,8)=wave_data(:,8)*((117-128)*0.5/128)+1;
wave_data(:,9)=wave_data(:,9)*((109-128)*0.5/128)+1;
%�����ֵ������
mean(1,1:9)=mean(wave_data(:,1:9));
var(1,1:9)=var(wave_data(:,1:9));

%��������Ҫ���������
test_data=csvread('D:\STM32Project\matlab\Test.csv');
%����ḡ����
test_data(:,1)=4*test_data(:,1)/32767;
test_data(:,2)=4*test_data(:,2)/32767;
test_data(:,3)=4*test_data(:,3)/32767;
test_data(:,4)=2000*test_data(:,4)/32767;
test_data(:,5)=2000*test_data(:,5)/32767;
test_data(:,6)=2000*test_data(:,6)/32767;
test_data(:,7)=test_data(:,7)*((114-128)*0.5/128)+1;
test_data(:,8)=test_data(:,8)*((117-128)*0.5/128)+1;
test_data(:,9)=test_data(:,9)*((109-128)*0.5/128)+1;
%������ȥ����ƫ
test_data(:,4)=test_data(:,4)-mean(1,4);
test_data(:,5)=test_data(:,5)-mean(1,5);
test_data(:,6)=test_data(:,6)-mean(1,6);

%�ۼ������ǣ�������5ms�Ĳ���
dt=0.005;
wave_data_x=[cumsum(test_data(:,4)*dt) ...
    cumsum(test_data(:,5)*dt) ...
    cumsum(test_data(:,6)*dt)];
%״̬������Ԫ��
X=[1;0;0;0];
%����״̬ת�ƾ��󣬾����е�����ֵ���������ı�
A=eye(4);
%�۲����C,�����ֵҪ����X�ʹ����Ƶ�ֵ�ı�
C=zeros(6,4);
%״̬����Э����ǶԽ����Զ�����
P=eye(4);
%Q���󣬹����������������Ҫ������
Q=diag([1 2 1 1]);
%����������
H=zeros(4,6);
%����R���󣬾��Ǽ��ٶȼƺʹ����Ƶ���������
R=diag([var(1:3) var(7:9)]);

%��ѭ������ʼ����
for k=1:4442
    %����A��������
    A(1,2)=-dt*test_data(k,4);
    A(1,3)=-dt*test_data(k,5);
    A(1,4)=-dt*test_data(k,6); 
    A(2,1)=dt*test_data(k,4);
    A(2,3)=dt*test_data(k,6);
    A(2,4)=-dt*test_data(k,5);
    A(3,1)=dt*test_data(k,5);
    A(3,2)=-dt*test_data(k,6);
    A(3,4)=dt*test_data(k,4);
    A(4,1)=dt*test_data(k,6);
    A(4,2)=dt*test_data(k,5);
    A(4,3)=-dt*test_data(k,4);
    Z=[test_data(k,1:3) test_data(k,7:9)]';
    C(1,1)=2*X(2,1);C(1,2)=-2*X(4,1);C(1,3)=2*X(1,1);C(1,4)=-2*X(2,1);
    C(2,1)=-2*X(2,1);C(2,2)=-2*X(1,1);C(2,3)=-2*X(4,1);C(2,4)=--2*X(3,1);
    C(3,1)=-2*X(1,1);C(3,2)=2*X(2,1);C(3,3)=2*X(3,1);C(3,4)=--2*X(4,1);
    C(4,1)=-2*X(1,1);C(4,2)=2*X(2,1);C(4,3)=2*X(3,1);C(4,4)=--2*X(4,1);
    X_buf(k,:)=X;
    X=A*X;%����״̬
    P=A*P*A'+Q;
    H=P*C'/(C*P*C'+R);
    X=X+H*(Z-C*X);
    P=(eye(4)-H*C)*P;
end