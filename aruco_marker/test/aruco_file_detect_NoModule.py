import cv2

# Define globals
MAX_SIZE = 406

# Define helper functions
def extractAruco(img):
    # Inverse threshold to get the inner contour
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, th = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY_INV)

    # Crop image
    contours, hierarchy = cv2.findContours(th, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours = contours[0]

    epsilon = 0.1 * cv2.arcLength(contours, True)
    approx = cv2.approxPolyDP(contours, epsilon, True)

    image_crop = gray[approx[0, 0, 1]:approx[2, 0, 1], approx[0, 0, 0]:approx[2, 0, 0]]

    # Return extracted image
    return image_crop

def findArucoID(inp_img):
    # Extract image
    im = extractAruco(inp_img)

    # Resize it to smaller size for check
    im = cv2.resize(im, (MAX_SIZE, MAX_SIZE))

    # Remove padding
    width = int(MAX_SIZE / 7)
    im = im[width:width * 6, width:width * 6]

    # Calculate ID
    ret_val = 0

    for y in range(5):
        y_center = int((y * width) + (width / 2))  # 정수로 변환
        x_center_1 = int(width + (width / 2))      # 정수로 변환
        x_center_2 = int(3 * width + (width / 2))  # 정수로 변환

        _val1 = int(im[y_center, x_center_1])  # im[y, x] format
        _val2 = int(im[y_center, x_center_2])  # im[y, x] format

        if _val1 == 255:
            _val1 = 1

        if _val2 == 255:
            _val2 = 1

        ret_val = ret_val * 2 + _val1
        ret_val = ret_val * 2 + _val2

    return ret_val

# Load image and find ArUco ID
image = cv2.imread("0.jpg")
ID = findArucoID(image)

print("Marker ID is", ID)
