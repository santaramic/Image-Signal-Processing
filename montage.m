% using imshowpair(montage), and resizing
clear all;
close all;
Q = imread('lighthouse.bmp');
[M N D]=size(Q)
Q_small = imresize(Q,0.3);
figure;
imshowpair(Q,Q_small,'montage')
 
Q_resize = imresize(Q_small,[M N]);
figure;
imshowpair(Q,Q_resize,'diff')
