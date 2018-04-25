package com.moneywhore

// Imports
import java.io.File

// List of compiler instructions used to match code
var compilerInstructions = listOf<String>("INCLUDE")

// More will be added later, takes the first part of an instruction and performs a task
fun precompiler(line:String):ArrayList<String> {

    var lineCut = line.split(" ")

    when(lineCut[0]) {

        "INCLUDE" -> return includeFile(lineCut[1].replace("<", ""))

    }

    return arrayListOf("")
}

// Function to return a code file in an arraylist line by line
fun includeFile(name:String):ArrayList<String> {
    var includedCode = ArrayList<String>()
    val codeFile = File(name)
    val code = codeFile.readLines()
    code.forEach { l -> includedCode.add(l) }
    return includedCode
}