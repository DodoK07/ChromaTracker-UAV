import cv2
import numpy as np

cap = cv2.VideoCapture(0)

lower_color = np.array(
    [100, 150, 50]
)  # The lower limit we consider to be the darkest/lightest shade of blue
upper_color = np.array(
    [140, 255, 255]
)  # The upper limit of what we would consider the most vivid/bright shade of blue

while True:
    # ret: Was the read operation successful (True/False), frame: The matrix of the read frame
    ret, frame = cap.read()

    if not ret:
        print("No Camera footage was available!")
        break

    # We convert the image from BGR format to HSV format (required for color analysis)
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # We find the pixels that fall within the HSV range we specified.
    # This process gives us a black-and-white image: Areas that fall within the range are WHITE, and those that do not are BLACK.
    mask = cv2.inRange(hsv_frame, lower_color, upper_color)

    # 4. We identify the outlines (contours) of the white areas on the mask (i.e., the detected color)
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        # We filter out small noise (speckled noise). We only consider objects with an area greater than 500 pixels.
        if cv2.contourArea(contour) > 500:
            x, y, w, h = cv2.boundingRect(contour)

            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            cv2.putText(
                frame,
                "Blue Object Detected",
                (x, y - 10),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.6,
                (0, 255, 0),
                2,
            )

    cv2.imshow("Live Camera Feed", frame)
    cv2.imshow("Color Mask (White-Black)", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()

cv2.destroyAllWindows()
