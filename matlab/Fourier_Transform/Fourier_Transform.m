clc;
close all;
clear all;

%��ȡ���ٶȻ����ٶ����ݺ���ѹ��΢���ٶ�����
wave_data=xlsread('D:\STM32Project\matlab\Fourier_Transform\ft.csv');
accSpeed=wave_data(3:end,14);
spl06Speed=wave_data(3:end,15);

fs=100;%����Ƶ��100Hz
T=1/fs;%��������10msһ��
N=128;%���ݵ���
n=0:N-1;
t=n/fs;


y=fft(spl06Speed,N);
m=abs(y);
f=n*fs/N;
plot(f,m);

% plot(y,spl06Speed);