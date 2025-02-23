from qreader import QReader
import cv2

# Create a QReader instance
qreader = QReader()

# Open the front camera (typically camera index 0, but it may vary)
cap = cv2.VideoCapture(0)

# Check if the camera is opened successfully
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

print("Starting QR Code detection. Press 'q' to quit.")

while True:
    # Capture a frame from the camera
    ret, frame = cap.read()
    if not ret:
        print("Error: Failed to capture frame.")
        break

    # Convert the frame to RGB (QReader expects RGB format)
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Use QReader to detect and decode QR codes
    decoded_text = qreader.detect_and_decode(image=rgb_frame)

    # Display the decoded text if a QR code is found
    if decoded_text:
        print("Decoded QR Code:", decoded_text)

    # Show the live camera feed
    cv2.imshow("QR Code Scanner", frame)

    # Press 'q' to quit the program
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close all OpenCV windows
cap.release()
cv2.destroyAllWindows()

