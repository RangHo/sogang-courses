import kotlin.collections.*

// Matrix X is row major
val x = arrayOf(
	intArrayOf(1, 2, 3),
    intArrayOf(4, 5, 6),
    intArrayOf(7 ,8, 9),
)

// Matrix Y is column major
val y = arrayOf(
	intArrayOf(1, 2, 3),
    intArrayOf(4, 5, 6),
    intArrayOf(7, 8, 9),
    intArrayOf(10, 11, 12),
)

// Print helper for row-major matrices
fun printRowMajor(matrix: Array<IntArray>) {
    for (row in matrix) {
        for (item in row) {
            print("$item\t")
        }
        println()
    }
}

// Print helper for column-major matrices
fun printColumnMajor(matrix: Array<IntArray>) {
    for (index in 0..(matrix[0].size - 1)) {
        for (col in matrix) {
            print("${col[index]}\t")
        }
        println()
    }
}

// Entrypoint
fun main() {
    var result = arrayOf<IntArray>()

    // For each row in X...
    for (xRow in x) {
        // A row of the result matrix (row-major)
        var resultRow = intArrayOf()

        // For each column in Y...
        for (yCol in y) {
            // Add a new row item (haha functional go brrr)
           	resultRow += (xRow zip yCol).fold(0) {
                total, item -> total + item.first * item.second
            }
        }

        // Add the row to the result
        result += resultRow
    }

    println("-- x --")
    printRowMajor(x)
    println()

    println("-- y --")
    printColumnMajor(y)
    println()

    println("-- result --")
    printRowMajor(result)
}
