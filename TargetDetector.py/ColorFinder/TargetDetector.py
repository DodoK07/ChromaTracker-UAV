import cv2
import numpy as np


class TargetDetector:
    """An image processing class for UAV autonomous locking and color tracking."""

    def __init__(self, lower_hsv, upper_hsv, deadzone_size=120):
        self.lower_hsv = np.array(lower_hsv)
        self.upper_hsv = np.array(upper_hsv)

        self.deadzone_size = deadzone_size

    def process_frame(self, frame):
        """Processes the live frame from the camera; rotates the target coordinates, orientation, and the processed image."""
        h, w, _ = frame.shape

        screen_center_x = w // 2
        screen_center_y = h // 2

        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        mask = cv2.inRange(hsv_frame, self.lower_hsv, self.upper_hsv)

        contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        target_center = None
        direction = "NO TARGET"

        for contour in contours:
            # To filter out noise, we only process images where the object is larger than 500 pixels
            if cv2.contourArea(contour) > 500:
                x, y, box_w, box_h = cv2.boundingRect(contour)

                # --- STEP 1: CALCULATING THE CENTER OF THE TARGET ---
                cx = x + (box_w // 2)
                cy = y + (box_h // 2)
                target_center = (cx, cy)

                cv2.rectangle(frame, (x, y), (x + box_w, y + box_h), (0, 255, 0), 2)

                cv2.circle(frame, (cx, cy), 5, (0, 0, 255), -1)

                # --- STEP 2: CALCULATING THE DEADZONE AND DIRECTION COMMAND ---
                delta_x = cx - screen_center_x
                delta_y = cy - screen_center_y

                half_dz = self.deadzone_size // 2

                # If the offset on the X and Y axes is outside the dead zone, we generate a direction command
                if abs(delta_x) > half_dz or abs(delta_y) > half_dz:
                    direction_parts = []
                    if delta_y < -half_dz:
                        direction_parts.append("TO UP")
                    elif delta_y > half_dz:
                        direction_parts.append("TO DOWN")

                    if delta_x < -half_dz:
                        direction_parts.append("TO LEFT")
                    elif delta_x > half_dz:
                        direction_parts.append("TO RIGHT")

                    direction = " / ".join(direction_parts)
                else:
                    direction = "LOCKED"

                # We display the target coordinates and the UAV command on the screen
                cv2.putText(
                    frame,
                    f"Target: ({cx}, {cy})",
                    (x, y - 10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 255, 0),
                    2,
                )
                break

        # --- STEP 3: DRAWING THE SCREEN CENTER AND DEADZONE ---
        cv2.line(
            frame,
            (screen_center_x - 15, screen_center_y),
            (screen_center_x + 15, screen_center_y),
            (200, 200, 200),
            1,
        )
        cv2.line(
            frame,
            (screen_center_x, screen_center_y - 15),
            (screen_center_x, screen_center_y + 15), (200, 200, 200),
            1,
        )

        dz_top_left = (
            screen_center_x - self.deadzone_size // 2,
            screen_center_y - self.deadzone_size // 2,
        )
        dz_bottom_right = (
            screen_center_x + self.deadzone_size // 2,
            screen_center_y + self.deadzone_size // 2,
        )
        cv2.rectangle(frame, dz_top_left, dz_bottom_right, (150, 150, 150), 1)

        color_code = (0, 255, 0) if "KILITLENDI" in direction else (0, 165, 255)
        cv2.putText(
            frame,
            f"IHA Komut: {direction}",
            (20, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            color_code,
            2,
        )

        return frame, target_center, direction


# ==================== TO USE / TEST BLOCK ====================
if __name__ == "__main__":
    LOWER_BLUE = [100, 150, 50]
    UPPER_BLUE = [140, 255, 255]

    detector = TargetDetector(
        lower_hsv=LOWER_BLUE, upper_hsv=UPPER_BLUE, deadzone_size=100
    )

    cap = cv2.VideoCapture(0)

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # We process the square by calling our class's main method
        processed_frame, center, cmd = detector.process_frame(frame)

        # We display the processed image on the screen
        cv2.imshow("UAV Autonomous Target Tracking Module", processed_frame)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()
