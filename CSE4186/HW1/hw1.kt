import java.io.File

/**
 * Test the functionality of the `also` function in Kotlin standard library.
 */
fun testAlso() {
    // Create a person builder
    val pb = PersonBuilder().also {
        // Set the name of the PersonBuilder instance
        it.name = "John Doe"
    }.also {
        // `also` can be chained like this, because it returns `this` (i.e. the PersonBuilder instance)!
        // Now let's set the jobName of the PersonBuilder instance
       	it.jobName = "Procrastinator"
    }

    // Now we can build a Person object using the PersonBuilder we just created
    val person = pb.build()

    // Hey, person, introduce yourself!
    person.introduce()
}

/**
 * Test the functionality of the `with` function in Kotlin standard library.
 */
fun testWith() {
    // Let's write something to a file using `with`
    val timestamp = with(File("testWith.txt"), {
        // If the file does not exist, make one
        if (!exists()) {
            createNewFile()
        }

        // Write the current time value
        val currentTime = System.currentTimeMillis()
        writeText(currentTime.toString())

        // Return the current time value to the caller!
        currentTime
    })

    // Print the current time so that we can verify later
    println("Written ${timestamp} to the file!")
}

/**
 * Test the functionality of the `run` function in Kotlin standard library.
 */
fun testRun() {
    // Extract the content of the file created when testing `with`
    val timestamp = File("testWith.txt").readText().toLong()

    // Let's assume a person's name depends on his/her birth timestamp
    // We can chain multiple scope functions with `run`
    val testResult = PersonBuilder().also {
        it.name = timestamp.toString()
        it.jobName = "Robot"
    }.run {
        // Build the person from `this` PersonBuilder instance
        val person = build()

        // Make sure he/she introduces him/herself
        person.introduce()

        // We can make sure that the jobName is indeed equal to profession
        // and send that information to the caller (it should be true always)
        jobName == person.profession
    }

    // This should always be true, but just for a good measure...
    if (testResult) {
        println("PersonBuilder#jobName is equal to Person#profession!")
    } else {
        println("PersonBuilder#jobName is NOT equal to Person#profession!")
    }
}

/**
 * Entrypoint.
 */
fun main() {
    println("== Testing `also` function ==")
    testAlso()
    println()

    println("== Testing `with` function ==")
    testWith()
    println()

    println("== Testing `run` function ==")
    testRun()
    println()
}

/**
 * Represents a person with a name and a profession.
 *
 * This class is created as a helper to test the inner workings of Kotlin scope functions.
 */
abstract class Person {
    val name: String

   	abstract val profession: String

    constructor(name: String) {
        this.name = name
    }

    fun greet() {
        println("Hello, ${this.name}!")
    }

    fun introduce() {
        greet()
        println("I am ${this.profession}.")
    }
}

/**
 * Builder to create an anonymous instance of Person.
 *
 * This class is created as a helper to test the inner workings of Kotlin scope functions.
 */
class PersonBuilder {
    lateinit var name: String

    lateinit var jobName: String

    fun build(): Person {
        return object: Person(name) {
            override var profession: String = jobName
            	private set
        }
    }
}
