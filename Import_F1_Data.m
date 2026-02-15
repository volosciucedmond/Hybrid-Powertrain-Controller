% Import the F1 data for Simulink

clear; clc;

% Read the CSV file
data = readmatrix('verstappen_monza_2025.csv');

% The CSV has a header row, so numeric data starts at row 2
% Column 1 = Time (s), Cloumn 2 = Speed (km/h)
raw_time = data(:, 1);
raw_speed_kph = data(:, 2);

% Data cleaning
% Remove any of the "NaN" errors that sometimes happen with imports
valid_indices = ~isnan(raw_time) & ~isnan(raw_speed_kph);
time_clean = raw_time(valid_indices);
speed_clean = raw_speed_kph(valid_indices);

% Physics check: convert to SI units (m/s)
% 300 km/h is abt 83 m/s
speed_ms = speed_clean / 3.6;

% Create the Simulink object using timeseries because it handles variable
% time steps automatically
Monza_Cycle = timeseries(speed_ms, time_clean);
Monza_Cycle.name = "Verstappen_Lap";

% Plot to confirm it looks like Monza
figure(1);
plot(time_clean, speed_clean, 'r', 'LineWidth', 1.5)
title("Target: Max Verstappen - Monza 2025 (Qualifying)")
xlabel('Time(s)');
ylabel('Speed (km/h)');
grid on;

disp('Data Ready! Variable Monza_Cycle is now in your Workspace!');