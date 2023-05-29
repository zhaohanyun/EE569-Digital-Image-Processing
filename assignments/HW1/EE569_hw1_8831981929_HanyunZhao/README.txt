# EE569 Homework Assignment #1
# Date: Jan 30, 2021
# Name: Hanyun Zhao
# ID: 8831981929
# email: zhaohanyun@usc.edu

# Compiled on WINDOWS 10

The project is huge, with too many files, using both C++ and python, and some compiling problem. I apologize I don't think it's very like to integrate everything in a makefile. Instead, this file briefly explain how to generate the answer for each question, subquestion, subsubquestion. The cammand is also included in the report.

First all the image materials are place in a folder name 'images'. The folder is in the same path with the project. All the image output will go to a folder name 'output'.

1.a
	g++ -o test BilinearDemosaicing.cpp
	test images/House.raw output/House_output.raw
	Output:House_output.raw

1.b.1
	g++ -o HistogramMani1 HistogramMani1.cpp
	python3 plot Histogram.py

1.b.2
	g++ -o HistogramMani1 HistogramMani1.cpp
	HistogramMani1 images/Hat.raw
	Output:MethodAEnhanced.raw

1.b.3
	g++ -o HistogramMani2 HistogramMani2.cpp
	HistogramMani2 images/Hat.raw
	Output:MethodBEnhanced.raw

1.c.2.1
	g++ -o clahe CLAHE.cpp
	clahe images/Taj_Mahal.raw output/TajMani1.raw
	Output:TajMani1.raw

1.c.2.2
	g++ -o clahe2 CLAHE2.cpp
	clahe2 images/Taj_Mahal.raw output/TajMani2.raw
	Output: TajMani2.raw

1.c.3
	g++ doesn't work
	In CMakeLists activate this line "add_executable(EE569_hw1_8831981929_HanyunZhao CLAHEcv.cpp)", then run project.

2.a.1
	g++ -o ImageDeno ImageDeno.cpp
	ImageDeno
	Output:Flower_gray_noise_Histo.txt
	python3 plotHistogram

2.a.2
	g++ -o ImgDenoMean ImgDenoMean.cpp
	ImgDenoMean images/Flower_gray_noisy.raw output/Flower_gray_DenoMean3.raw 3
	Output(PSNR): 31.3409
	Flower_gray_DenoMean3.raw

	g++ -o ImgDenoMean ImgDenoMean.cpp
	ImgDenoMean images/Flower_gray_noisy.raw output/Flower_gray_DenoMean5.raw 5
	Output(PSNR): 28.1684
	Flower_gray_DenoMean5.raw

	g++ -o ImgDenoGauss ImgDenoGauss.cpp
	ImgDenoGauss images/Flower_gray_noisy.raw output/Flower_gray_DenoGauss3.raw 3
	Output(PSNR): 32.426
	Flower_gray_DenoGauss3.raw

2.b.1
	g++ -o BilateralFilter BilateralFilter.cpp
	BilateralFilter images/Flower_gray_noisy.raw output/Flower_gray_BiFi.raw 3
	Output(PSNR): 32.659
	Flower_gray_BiFi.raw 3

	g++ -o ImgDenoGauss ImgDenoGauss.cpp
	ImgDenoGauss images/Flower_gray_noisy.raw output/Flower_gray_DenoGauss5.raw 5
	Output(PSNR): 31.1134
	Flower_gray_DenoGauss5.raw

2.c.1
	In CMakeLists activate this line"add_executable(EE569_hw1_8831981929_HanyunZhao NLMcv.cpp)" and run project

2.d.1
	In MixNoiseColor.cpp main() function, activate this line "analyzeNoise(Imagedata,ImagedataSrc);"
	In CMakeLists activate this line"add_executable(EE569_hw1_8831981929_HanyunZhao MixNoiseColor.cpp)" and run project

2.d.3
	In MixNoiseColor.cpp main() function, activate this line "Denoise(Imagedata,ImagedataSrc,ImagedataOut);"
	In CMakeLists activate this line"add_executable(EE569_hw1_8831981929_HanyunZhao MixNoiseColor.cpp)" and run project

3.1
	g++ -o FrostedGlassFilter FrostedGlassFilter.cpp
	FrostedGlassFilter images/Flower.raw output/Flower_Frosted_5.raw 3 5
	Output: Flower_Frosted_5.raw

	g++ -o FrostedGlassFilter FrostedGlassFilter.cpp
	FrostedGlassFilter images/Flower.raw output/Flower_Frosted_7.raw 3 7
	Output: Flower_Frosted_7.raw

3.2
	FrostedGlassFilter images/Flower_noisy.raw output/Flower_noisy_Frosted_5.raw 3 5
	Output: Flower_noisy_Frosted_5.raw

	FrostedGlassFilter images/Flower_noisy.raw output/Flower_noisy_Frosted_7.raw 3 7
	Output: Flower_noisy_Frosted_7.raw

3.3
First denoise then forsted:
	FrostedGlassFilter output/Flower_gray_DenoGauss5.raw output/Flower_gray_noisy_DenoFro_5.raw 1 5
	Output: Flower_gray_noisy_DenoFro_5.raw

First forsted then denoise:
	FrostedGlassFilter images/Flower_gray_noisy.raw output/Flower_gray_noisy_Frosted_5.raw 1 5
	Output: Flower_gray_noisy_Frosted_5.raw

	ImgDenoGauss output/Flower_gray_noisy_Frosted_5.raw output/Flower_gray_FroDeno_5.raw 5
	Output: Flower_gray_FroDeno_5.raw