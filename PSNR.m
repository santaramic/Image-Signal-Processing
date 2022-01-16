%%
clear all; close all;

ori_img = imread('doll.bmp');

imwrite(ori_img, 'doll_Q_5.jpg', 'Quality', 5);
imwrite(ori_img, 'doll_Q_100.jpg', 'Quality', 100);

img_comp_5 = imread('doll_Q_5.jpg');
img_comp_100 = imread('doll_Q_100.jpg');

M1 = size(img_comp_5);
M2 = size(img_comp_100);

MSE_5 = sum(sum((img_comp_5 - ori_img).^2))/(M1(1) * (M1(2));
AMSE_5 = (MSE_5(1) + MSE_5(2) + MSE_5(3)) / 3;
PSNR_5 = 10 * log10(255^2/AMSE_5); %30.7158
                                             
MSE_100 = sum(sum((img_comp_100 - ori_img).^2))/(M2(1) * (M2(2));
AMSE_100 = (MSE_100(1) + MSE_100(2) + MSE_100(3)) / 3;
PSNR_100 = 10 * log10(255^2/AMSE_100); %43.1022
