Version Information
-------------------

     pk2cmd -? V

    Executable Version: 1.20.00 
    Device File Version: 1.55.00 
    OS Firmware Version: 2.32.00 

    Operation Succeeded 


Auto-detect Device
------------------

    pk2cmd -P 
    Auto-Detect: Found part PIC12F675. 

    Operation Succeeded 


Read OSCCAL (configuration memory)
----------------------------------

    pk2cmd -P PIC12F675 -GP 0x3F8-0x3FF 
    Read successfully. 

    Program Memory 
    000003F8 003FFF  003FFF  003FFF  003FFF  003FFF  003FFF  003FFF  003454   

    Operation Succeeded


Write Hex-file to PIC
---------------------

    pk2cmd -P PIC12F675 -X -M -F code.hex 
    PICkit 2 Program Report 
    16-8-2012, 10:21:05 
    Device Type: PIC16F630 

    Program Succeeded. 

    Operation Succeeded 


Erase
-----

    pk2cmd -P PIC12F675 -X -E 
    Erasing Device... 

    Operation Succeeded


Verify
------

    pk2cmd -P PIC12F675 -Y -F code.hex
    PICkit 2 Verify Report
    16-8-2012, 10:28:59
    Device Type: PIC12F675

    Verify Succeeded. 

    Operation Succeeded 


Help
----

    pk2cmd -?
