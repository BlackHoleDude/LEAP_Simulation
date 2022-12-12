# Large Area Burst Polarimeter (LEAP)
## LEAP-201 Configuration

### How to build and run the simulation
1. Compile and link to generate an executable with cmake.

```
        % cd $HOME/LEAPsim      # go to directory which contains your code
        % mkdir build     		# make a directory for the build
        % cd build
        % cmake ..				# run cmake
        % make -j N             # "N" is the number of processes (optional)
```


2. Execute in 'INTERACTIVE MODE' with visualization.

``` 
% When started up without a macro file, the program starts up in interactive mode, 
% with a display of the LEAP mass model.
% As it starts up in interactive mode, it executes both init_vis.mac and vis.mac. 
% Subsequent execution of the vis_test1.mac macro generates some sample output.

       % cd $HOME/LEAPsim/build
       % ./startSIM
       > /control/execute vis_test1.mac 
       ...
       > exit
```

3. Execute in 'BATCH' mode from macro file.

```
% Use of the "-m" option specifies use of a batch macro file.

        % cd $HOME/LEAPsim/build
        % ./startSIM -m macros/batch_test1.mac               # run macro batch_test1.mac
        % ./startSIM -m macros/batch_test1.mac -t 4          # run macro batch_test1.mac and set number of threads to 4
        % ./startSIM -m macros/batch_test1.mac >& SIM.out    # redirecting output to a file
```


4. Simulate polarized mono-energetic source in 'BATCH' mode from macro file.

```
% Use of the "-m" option specifies use of a batch macro file.

        % cd $HOME/LEAPsim/build
        % ./startSIM -m macros/LEAPsim-E0133-AZI000-ZEN00.mac
        
% Summary analysis with LEAP_sim_pol_mono_analysis.py

```


5. Simulate polarized continuum source in 'BATCH' mode from macro file.

```
% Use of the "-m" option specifies use of a batch macro file.

        % cd $HOME/LEAPsim/build
        % ./startSIM -m macros/LEAPsim-CRAB-ZEN00.mac
        
% Summary analysis with LEAP_sim_pol_cont_analysis.py

       
```


6. Simulate polarized GRB source in 'BATCH' mode from macro file.

```
% Use of the "-m" option specifies use of a batch macro file.

        % cd $HOME/LEAPsim/build
        % ./startSIM -m macros/LEAPsim-SGRBSTD-E0000-AZI000-ZENscan.mac

% Summary analysis with LEAP_sim_pol_grb_analysis.py
      
        
```
