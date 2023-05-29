function[image]=readraw2(width,height,file)
    f=fopen(file,'r');
    data=fread(f);
    image=reshape(data,height,width,1);%1 is num of channels
    image=image/255;
    fclose(f);
end