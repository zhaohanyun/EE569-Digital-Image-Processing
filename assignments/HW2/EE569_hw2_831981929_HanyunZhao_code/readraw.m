function[image]=readraw(width,height,file)
    f=fopen(file,'r');
    data=fread(f);
    image=reshape(data,height,width,1);%1 is num of channels
    fclose(f);
end


