# Nova
*Ethan Pinto* developed and designed **Nova**, an interpreted programming language written using C++, in *April, 2023*. With a straightforward syntax for quick and simple programming, the language is designed to be user-friendly for beginners. The runtime interpretation of code in Nova allows quick experimentation and prototyping. The language was designed to be simple to learn and use,* especially for those who are new to programming*. Nova source code is open-source software, and it is available to everyone on **GitHub**.

------------


> *The original intent was to create a programming language easy enough for anyone to learn.*
-*Ethan Pinto*

------------


	 # This declares a variable with the value "This variable is a string!"
    def myVariableName = "This variable is a string!"
	
	# This outputs a normal message to the console.
    print "this is a print message!"
	
	# This pauses the program until the user allows for it to continue.
    suspend() 
	
	# This outputs a different type of message to the console, with its line number.
    warn "this is a warn message!"
	
	# This force quits the program.
    expel()
	

the result of the code above is as follows:

> this is a print message!
Code interpretation suspended. Type 1 to continue, or -1 to expel.
1
(4) WARN: this is a warn message!
Code interpretation expelled.
