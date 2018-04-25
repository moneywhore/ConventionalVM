package com.moneywhore
// This file can also be known as the second pass. It converts labels, calls, etc into usable addresses for the VM

// Label dictionary, contains the addresses of the labels
class Variable constructor(var labelDict:HashMap<String,String> = hashMapOf<String, String>()){

    // Creates a definition for a label
    fun handleLabel(line: String, lineNumber: Int): String {

        labelDict.set(line, Integer.toString(lineNumber))

        return "nop"

    }

    // Replaces any possible label in a line
    fun replaceLabelNames(line: String): String {
        var newLine = line
        labelDict.keys.forEach { s -> newLine = newLine.replace(s, labelDict.getValue(s)) }
        return newLine
    }
}