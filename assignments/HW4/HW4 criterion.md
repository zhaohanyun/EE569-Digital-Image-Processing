Dear EE569 students,



We have published your grades of homework #4. Please find the grading rubric below, if you have any grading issues or doubts, please feel free to send an email to Peida Han before Sat, April 16, 23:59. Thanks!



**Problem 1: (35')**

**(a)(15’)**

- 3D plot: (5’)
- Feature dimension 2 and 11 ('L5E5' and 'S5L5'). (5’)
- Nearest neighbor: Error rate is: 4/12: 33%. (test image #1, #3, #8, #11 are wrong). (5’)

**(b)(20’):**

- Unsupervised. K-means (5’)

​      25D features (2’): error rate = 4/12 = 33.33% (give full credit to 4 or less errors)

​      3D features (2'): error rate = 5/12 = 42% (give full credit to 5 or less errors)

- Discussion on effectiveness of PCA (2'): Since PCA keeps the most important data and disregards the misleading data, it contributes to the performance and efficiency of k-means clustering. We can see this in error rates.

- Random Forest (6'): error rate = 2/12 = 16.67% (2 errors or less receives full credit)
- SVM (5'): error rate = 4/12 = 33.33% (4 errors or less receives full credit.)
- Compare two classifiers (2%).

**Problem 2: (30')**

**(a)(20')![img](https://lh6.googleusercontent.com/dIJtqTkqz2QlJHnBaoCyX7Lw4UAgGdc3sdbZ2YPuxmP2Ih0L1y5KOJjZAhg5-WwGKuYB41uO_n4ZTJHqZOP7Q-AGQW7BpDTSXdDpFK1dLKMm7Hq1ORxLIMsjJSSPKK8bODlbrg_3)**

- Results of least 2 window sizes. (10’)
- Explanation on why the segmentation fails in some areas. (5%)
- Comparison on window size: Larger window size has two effects: (1) less accurate segmentation near boundaries. (2) smoother segmentation far from the edges. (5')

**(b)(10')** Results do not show obvious enhancement. (6’)

 

**Problem 3 (35'):**

**(a)(10'): each question: 2'** 

![img](https://lh3.googleusercontent.com/PY8FVDTgIyJ8Sij5tT2Pev1t2-NV2K2L-_Lk4g81rzX5cF0rmnlWlbZpwkYDPrGuwqAkDl-jjgu1ZzZvam8usdoog6eNpUdDWDj2tykl5WLFrdlTGWyHyN-oYVu75-2RMlivSK2G)

​     **128-D also receive full credits.** 

**(b)(15'):**

(Different Hyperparameters have different results. If one use the default one, it should be exactly the same as below. If one tunes the hyperparameters, need to state it, and will receive credits as long as they can present the key points.)

  Largest scale in Cat_1 match with nearest neighbor in Cat_Dog. Discuss the results (3’)

  Largest scale in Dog_1, match with nearest neighbor in Cat_Dog (3’)

  Largest scale in Cat_1, match with nearest neighbor in Cat_2:(3’)

  Largest scale in Cat_1, match with nearest neighbor in Dog_1:(3’)

Show and comment on the matching results. Explain why it works or fails in some cases

Some possible explanations on failure cases (3’):

- The field of view in pair are different.
- Although the images are all dogs (or cat) they are not completely the same dog (or cat), so that we may not match their features successfully.
- Nearest neighbor does not necessarily show the best match;
- Any other explanation that makes sense to you is acceptable.

**(c) (10')** 

Histograms are required.

(1) Using original 128-D features. (May not be exactly the same, because the ordering of 8 code

words can change).

![img](https://lh4.googleusercontent.com/TdlOXjmaM3D0n5B4VbpIhC0MjsfK1XaDv6lCCXoRQhKGL5ZIe8tK8MCgKjRBKiE6JgdyfTmPT51UkKApWiiy_fiFCgw-3Y7dqiPuKT9l9zJc7LBaKzV8KgVyaRk5ifShOv-nmPm_)

• Similarity of dog2 with cat1: 0.75

• Similarity of dog2 with dog1: 0.69

5' Histograms

3’ Similarity indices (give credit for -0.05 ~ +0.05 of above values).

2' Discussion on observations. For example, why the matching may fail (which is expected to be dog matches better with dog, but may not).

**

**