import cv2 #导入opencv库


def face_detect_demo():
    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY) #变灰预处理
    face_detector = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalcatface.xml')  #调用级联分类器以及xml人脸模型
    faces = face_detector.detectMultiScale(gray, 1.03, 1) #人脸识别
    face = 0
    for (x, y, w, h) in faces:
        cv2.rectangle(src, (x, y), (x + w, y + h), (0, 0, 255), 2) #调用矩形绘图工具绘制识别的人脸区域
        cv2.imshow("result", src)
        output = src[y : y + h,x : x + w] #截取指定识别的人脸区域图像
        resizesrc = cv2.resize(output, (32,32)) #32×32处理
        out = cv2.cvtColor(resizesrc, cv2.COLOR_BGR2GRAY) #灰度处理
        face = face + 1
        name = 'face' + str(face) + '.png'
        cv2.imwrite(name, out)

#调用函数，并且将输入图像与输出图像在不同窗口输出
src = cv2.imread("1.jpg")
cv2.namedWindow("input image", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("result", cv2.WINDOW_AUTOSIZE)
cv2.imshow("input image", src)
face_detect_demo()
cv2.waitKey(0)
cv2.destroyAllWindows() #键入操作即可停止运行
