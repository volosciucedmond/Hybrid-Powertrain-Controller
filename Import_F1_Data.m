% Import the F1 data for Distance-Based Lookup
clear; clc;


% 1. Read the CSV file
data = readmatrix('verstappen_monza_2025.csv');

% 2. Extract raw data
raw_time = data(:, 1);
raw_speed_kph = data(:, 2);

% 3. Data cleaning
valid_indices = ~isnan(raw_time) & ~isnan(raw_speed_kph);
time_clean = raw_time(valid_indices);
speed_clean = raw_speed_kph(valid_indices);

% 4. Physics Conversion (m/s is required for integration)
speed_ms = speed_clean / 3.6; 

% 5. CALCULATE DISTANCE (The Critical Step)
% We use cumulative trapezoidal integration to find the track position (m)
% at every timestamp of the telemetry.
dist_ref = cumtrapz(time_clean, speed_ms);

% 6. Prepare Reference for 1-D Lookup Table
% Simulink's Lookup Table works best with standard arrays in the workspace
monza_dist_axis = dist_ref;
% Smooth the speed data to remove the "jitter"
monza_speed_target = smoothdata(speed_ms, 'gaussian', 5); 
% The '50' is the window size. Increase if still too jittery.

% --- Add this to Import_F1_Data.m ---
% Calculate Acceleration (dv/dt)
% limit noise by using a gradient function
monza_accel_raw = gradient(speed_ms, time_clean);
monza_accel_smooth = smoothdata(monza_accel_raw, 'gaussian', 5);

% Create Timeseries for Simulink
Monza_Speed_TS = timeseries(speed_ms, time_clean);
Monza_Accel_TS = timeseries(monza_accel_smooth, time_clean);

%% --- ADD THIS TO Import_F1_Data.m ---
% 7. Calculate Reference Acceleration (Physics Stress Test)
% We calculate dv/dt to know how much Force is required at any moment.
accel_g = gradient(monza_speed_target, time_clean); % derivate speed
monza_accel_target = smoothdata(accel_g, 'gaussian', 5); % smooth noise

% 8. Define "Stress" Parameters
% 2025 Regs: Min Mass = 800kg (Art 4.1)
mass_kg = 800; 
% Monza Low Drag Setup (Estimated CdA)
CdA = 1.05; 
rho = 1.225; % Air density

% Calculate the Total Force required to match Max's Lap
% F_total = F_inertial + F_drag + F_roll
F_aero = 0.5 * rho * CdA * (monza_speed_target.^2);
F_inertial = mass_kg * monza_accel_target;
F_roll = mass_kg * 9.81 * 0.015; % Rolling resistance
F_required_total = F_aero + F_inertial + F_roll;

% Create Timeseries for Simulink inputs
Ref_Force_TS = timeseries(F_required_total, time_clean);
Ref_Speed_TS = timeseries(monza_speed_target, time_clean);

% Reduce cornering speed by 3% to simulate 2025 tire degradation
% We assume any speed < 250 kph is a "corner"
is_corner = monza_speed_target < (250/3.6); 
monza_speed_target(is_corner) = monza_speed_target(is_corner) * 0.97;
Monza_Cycle = timeseries(speed_ms, time_clean);
% 7. Plot to confirm track layout (Speed vs. Distance)
figure(1);
plot(monza_dist_axis, speed_clean, 'b', 'LineWidth', 1.5)
title("Spatial Reference: Verstappen - Monza 2025")
xlabel('Distance (m)');
ylabel('Speed (km/h)');
grid on;

disp('Data Ready! Use "monza_dist_axis" and "monza_speed_target" in your Lookup Table.');