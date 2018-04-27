package com.moneywhore
// Imports
import java.io.File
import java.util.*
import kotlin.collections.ArrayList

// Store the code into an array of lines
var code = ArrayList<String>()

// Easy template to use for math operators
var maths = hashMapOf<String, String>("+" to "pop r0\npop r1\nadd r2 r0 r1\npush r2",
                                    "-" to "pop r0\npop r1\nsub r2 r0 r1\npush r2",
                                    "*" to "pop r0\npop r1\nmul r2 r0 r1\npush r2",
                                    "/" to "pop r0\npop r1\ndiv r2 r0 r1\npush r2")

// List of simple commands to check the start of a string to
var simpleCommands = listOf(";", "@", "=", "#")

// Handle and process simple commands
fun simpleCommands(line:String):String {
    var prefix = line.get(0)

    when(prefix) {

        ';' -> return ret()
        '@' -> return call(line.substring(1))
        '=' -> return jmpeq(line.substring(1))
        '#' -> return inline(line.substring(1).trim(' '))

    }

    return ""
}

// Simple, easy functions
fun label(line:String):String {
    return "LABEL " + line + "\n"
}

fun call(label:String):String {
    return "loadi r0 " + label + "\ncall r0"
}
fun ret():String {
    return "ret"
}
fun jmpeq(line:String):String {
    return "pop r0\npop r1\ncmp r0 r1\njmpeq " + line
}
fun inline(line:String):String {
    return line.replace(";", "\n")
}
fun end():String {
    return "halt"
}
fun defaultHandle(line:String):String {
    return "pushl " + line
}

// More complex functions
fun getRandLabel():String {
    return Integer.toString(Random().nextInt(1000000000))
}

fun printStr(line:String):String {
    var startLoopName = getRandLabel()
    var stopLoopName = getRandLabel()

    var startLoopPrint = getRandLabel()
    var stopLoopPrint = getRandLabel()

    var finalString = ""

    if (line.split(" ")[1] == "mem") {
        // Create the start of the reading loop, and set r0 equal to 0 (this is to check if the string is terminated)
        finalString = finalString + "loadi r1 0\n" + "LABEL " + startLoopName + "\n"

        // Read memory value, check if equal to zero, stop loop if is, restart if not
        finalString = finalString + "sdec 1\n" + "rcur r0\n" + "cmp r0 r1\n" + "jmpeq " + stopLoopName + "\n" + "jmp " + startLoopName + "\n" + "LABEL " + stopLoopName + "\n"

        // Create label for print loop
        finalString = finalString + "LABEL " + startLoopPrint + "\n"

        // Read memory value, compare to zero, if it is stop loop, if not print and restart
        finalString = finalString + "sinc 1\n" + "rcur r0\n" + "cmp r0 r1\n" + "jmpeq " + stopLoopPrint + "\n" + "int 0\n" + "jmp " + startLoopPrint + "\n" +  "LABEL " + stopLoopPrint + "\n"

        return finalString
    }

    else {
        line.split('"')[1].forEach { letter -> finalString = finalString + "loadi r0 " + letter.toInt() + "\n" + "int 0" + "\n"}
    }

    return finalString
}

fun getStr():String {
    var startLoopName = getRandLabel()
    var stopLoopName = getRandLabel()
    var finalString = ""

    // Just make sure that the string is terminated by a zero
    finalString = finalString + "pushl 0" + "\n"

    // Create the start of the getChar() loop
    finalString = finalString + "LABEL " + startLoopName + "\n"

    // Get the character typed, check if the key is enter
    finalString = finalString + "int 1\n" + "push r0\n" + "loadi r1 13\n" + "cmp r0 r1\n" + "\n"

    // If it is enter, end the loop, and jump back to the start if not
    finalString = finalString + "jmpeq " + stopLoopName + "\n" + "jmp " + startLoopName + "\n"


    // Push 0 to again signify termination
    finalString = finalString + "pushl 0" + "\n"

    // Define the stop loop at the end to continue normal execution
    finalString = finalString + "LABEL " + stopLoopName + "\n"

    return finalString
}

// Main code stuff
fun main(arg:Array<String>){

    var filename = "C:\\Users\\Flamingo\\Documents\\GitHub\\ConventionalVM\\Assemblr\\prog.fe"
    if(arg.size > 1){
        filename = arg[0]
    }
    print(filename)
    val codeFile = File(filename)
    var preCode = ArrayList<String>()
    preCode.add("@main")
    preCode.add("end")
    preCode.addAll(ArrayList<String>(codeFile.readLines()))
    code = interpret(preCode)
    code.removeAll(arrayListOf(""))
    code = labelCalc(code, 1)
    code = labelCalc(code, 2)
    print("\n\n")
    print(code.joinToString("\n"))

}