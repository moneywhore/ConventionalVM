package com.moneywhore

val varClass = Variable()

fun interpret(lines:ArrayList<String>):ArrayList<String> {

    var interpretedCode = ArrayList<String>()
    var lineCount = 0
    lines.forEach newLine@{ it ->
        lineCount += 1
        if (simpleCommands.contains(it.get(0).toString())) {
            interpretedCode.addAll(simpleCommands(it).split("\n"))
            return@newLine
        }

        if (it.split(" ")[0] == "printStr") {
            interpretedCode.addAll(printStr(it).split("\n"))
            return@newLine
        }

        if (it.split(" ")[0] == "getStr") {
            interpretedCode.addAll(getStr().split("\n"))
            return@newLine
        }

        if (it.get(0).toString() == ":") {
            interpretedCode.addAll(label(it.substring(1)).split("\n"))
            return@newLine
        }

        if (maths.keys.contains(it)) {
            interpretedCode.addAll(maths.getValue(it).split("\n"))
            return@newLine
        }

        if (it == "end") {
            interpretedCode.addAll(end().split("\n"))
            return@newLine
        }

        interpretedCode.add(defaultHandle(it))
    }

    return interpretedCode

}
fun labelCalc(lines:ArrayList<String>, pass:Int):ArrayList<String> {

    var lineCount = 0

    var calculatedCode = ArrayList<String>()

    lines.forEach labelLine@{ it ->
        lineCount += 1
        if (pass == 1) {
            if (it.split(" ")[0] == "LABEL") {
                calculatedCode.add(varClass.handleLabel(it.split(" ")[1], lineCount))
                return@labelLine
            }
        }
        else {
            if (it.split(" ")[0] == "jmp" || it.split(" ")[0] == "jmpeq") {
                calculatedCode.add(varClass.replaceLabelNames(it))
                return@labelLine
            }
        }

        calculatedCode.add(it)
    }

    return calculatedCode
}