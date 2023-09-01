
## PURPOSE: 
# this program generates the 'capture sequence.tap' gcode, exclusing the machine start and
# machine end parts of the program. The purpose of this GCODE is to move the CNC and capture 
# photos of the wound model using the Shark HD520 CNC machine. 

## PARAMETERS:
# number of captures - the number of photos to be taken at each interval
# spanMM - the total distance covered from the starting position (the starting position for testing is 150 mm)
# quantizationIncriment - the change in distance covered by each interval

numberOfCaptures = 6
spanMM = 350
quantizationIncriment = 5
overflowPadding = 30

numberOfCapturesPerCycle = int(spanMM/quantizationIncriment)+1
position = 0

open('capture sequence.tap', 'w').close()
with open("capture sequence.tap","w") as f:
    
    f.write("( CAPTURE SEQUENCE )\n")
    f.write("( this is the capture program used to create the uncertainty analysis data )\n")
    f.write("( each block labled 'CAPTURE NUMBER :#' was generated using 'capture sequence generator.py' )\n")
    f.write("( the working parameters are as follows; )\n")
    f.write("( span: {} mm )\n".format(spanMM))
    f.write("( incriment: {} mm )\n".format(quantizationIncriment))
    f.write("( start distance: 150 mm )\n")
    f.write("( photos per distance: {} )\n".format(numberOfCaptures))

    # Start the machine:
    f.write("( MACHINE START )\n")
    f.write("G21\n")
    f.write("G90\n")
    f.write("F150\n")
    f.write("S17000\n")
    f.write("M03\n")
    f.write("G00  X0.000  Y0.000 Z0.000\n")
    f.write("G04 P1\n")

    # Capture the samples
    for i in range(numberOfCaptures):
        factor = i%2*(-2) + 1
        for n in range(numberOfCapturesPerCycle):
            
            if factor>0:
                position = n*quantizationIncriment
            elif factor<0:
                position = spanMM - n*quantizationIncriment
            
            f.write("( CAPTURE NUMBER: {} )\n".format(n+i*numberOfCapturesPerCycle))
            f.write("G00 X0.000 Y{}.000 Z0.000\n".format(-position))
            f.write("G04 P.11\n")
            f.write("S18000\n")
            f.write("G04 P.44\n")
            f.write("S17000\n")
            f.write("G04 P.6\n")
        f.write("( HALT TO STANDARDIZE TIME INTERVALS )\n")
        f.write("G04 P.412\n")

    # Add overflow:
    for i in range(int(overflowPadding/2)):
        f.write("( OVERFLOW: {} )\n".format(2*i))
        f.write("G04 P1\n")
        f.write("G01 X0.000 Y0.000 Z5.000\n")
        f.write("G04 P1\n")
        f.write("( OVERFLOW: {} )\n".format(2*i+1))
        f.write("G04 P1\n")
        f.write("G01 X0.000 Y0.000 Z0.000\n")
        f.write("G04 P1\n")

    # Stop the machine: 
    f.write("( MACHINE END )\n")
    f.write("G04 P.8\n")
    f.write("G00 X0.000 Y0.000 Z5.080\n")
    f.write("G00  Z20.320\n")
    f.write("G00  X0.000  Y0.000\n")
    f.write("M02\n")