%%
clear all; close all;
ori_img = imread('doll.bmp');
imwrite(ori_img, 'doll_Q_5.jpg', 'Quality', 5);
img_comp_5 = imread('doll_Q_5.jpg');
imshowpair(ori_img, img_comp_5, 'montage');
% block boundary effects

%%
clear all; close all;
ori_img = imread('doll.bmp');

imwrite(ori_img, 'doll_Q_5.jpg, 'Quality', 5);
imwrite(ori_img, 'doll_Q_100.jpg, 'Quality', 100);

img_comp_5 = imread('doll_Q_5.jpg');
img_comp_100 = imread('doll_Q_100.jpg');

imshowpair(img_comp_5, img_comp_100, 'montage');
s1 = dir('doll_Q_5.jpg');
s2 = dir('doll_Q_100.jpg');
s = s2.bytes/s1.bytes % 24.7485
