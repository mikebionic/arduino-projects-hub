from serial import Serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

N = 50                  # Number of data points
max_distance = 50       # Maximum distance in cm
radar_color = "#55D020" # Color of radar lines
data_color = "r"        # Color of data points
port = "COM17"   # Serial port to use
baudrate = 9600         # Baud rate

def main():
    # Open serial port, make sure the port is correct for your setup.
    # Serial port connection restarts the Arduino.
    ser = Serial(port=port, baudrate=baudrate, timeout=1)

    # Wait for Arduino to be ready
    while ser.readline().decode("ascii").strip() != "Ready":
        pass

    # Create figure and data
    fig, ax = plt.subplots(subplot_kw={"projection": "polar"})
    ax.set_xlim([0.0, np.pi]) 
    ax.set_ylim([0.0, max_distance])

    ax.tick_params(color=radar_color, labelcolor=radar_color)
    for spine in ax.spines.values():
        spine.set_edgecolor(radar_color)
    ax.grid(color=radar_color)

    data_plot, = ax.plot([], marker="o", markersize=2, linestyle="None", color=data_color, zorder=10)
    line_plot, = ax.plot([], color=radar_color, alpha=0.5)

    data = np.zeros((N, 2))
    angles = np.hstack([np.arange(15, 166), np.arange(164, 14, -1)])

    # Define animation
    def animate(frame):
        i = frame % N
        angle = angles[frame % len(angles)]

        # Move servo and fetch data from serial port
        ser.write(bytes([angle]))
        line = ser.readline().decode("ascii").strip()
        if not line:
            return

        # Parse data
        num = [float(x) for x in line.split(",")]
        if len(num) != 2:
            return
        num[0] = np.deg2rad(num[0])

        # Update data and plot
        data[i] = num
        data_plot.set_data(data[:, 0], data[:, 1])
        line_plot.set_data([num[0], num[0]], [0, max_distance])

        return data_plot, line_plot
    
    # Create animation
    ani = animation.FuncAnimation(fig, animate, interval=30)
    plt.show()

    ser.close()

if __name__ == "__main__":
    main()
