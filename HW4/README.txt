Kevin Nash (kjn33)

Homework 4 Report
    
    [Outputs]
        
        { HW4 }  » ./hw4_1
        min = -97.27

        { HW4 }  » ./hw4_2_client
        Sent my min value

        { HW4 }  » ./hw4_2_server
        min = -97.27

        { HW4 }  » ./hw4_3
        min = -97.27        

    [Findings]

        The above outputs are shown completely unmodified. I would certainly
        not choose client/server because the overhead and chance of failure
        (assuming everything is done locally). Between forking and multi-
        threading, the end result seems about the same. The question is
        whether you want the easier part to be in setting up multiple threads/
        processes (easier with forking) or in setting up shared memory (easier
        with multi-thread than multi-process).
