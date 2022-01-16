clc, clear
im =rgb2gray(imread('doll.bmp'));
im2 =rgb2gray(imread('doll.bmp'));
[m,n]=size(im);
T=128; % threshold
im_T=zeros(m,n);
 
for i=1:m-1
    for j=2:n-1
        if im(i,j) < T
            im_T(i,j)=0;
            error=im(i,j);
        else
            im_T(i,j)=255;
            error=im(i,j)-255;
        end
        im(i,j+1)=im(i,j+1)+7*error/16;
        im(i+1,j-1)=im(i+1,j-1)+3*error/16;
        im(i+1,j)=im(i+1,j)+5*error/16;
        im(i+1,j+1)=im(i+1,j+1)+error/16;
    end
end
 
imdouble = im2double(im2);
T2=0.5;
im_T2=zeros(m,n);
for i=1:m-1
    for j=2:n-1
        if imdouble(i,j) < T2
            im_T2(i,j)=0;
            error2=imdouble(i,j);
        else
            im_T2(i,j)=1;
            error2=imdouble(i,j)-1;
        end
        imdouble(i,j+1)=imdouble(i,j+1)+7*error2/16;
        imdouble(i+1,j-1)=imdouble(i+1,j-1)+3*error2/16;
        imdouble(i+1,j)=imdouble(i+1,j)+5*error2/16;
        imdouble(i+1,j+1)=imdouble(i+1,j+1)+error2/16;
    end
end
 
figure;
imshowpair(im,imdouble,'montage')
