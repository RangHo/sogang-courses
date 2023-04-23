/**
 * A class representing an animal.
 */
interface Animal {
    abstract fun cry(): String
}

/**
 * A class representing an animal that can bark: dogs, wolves, etc.
 */
class BarkingAnimal: Animal {
    override fun cry(): String = "Woof!"
}

/**
 * Let's define a robot that mimics an animal. It is not an animal, but it behaves like one.
 */
class AnimalRobot(crier: Animal) : Animal by crier // This `by` clause delegates the call of `cry` to the `crier` field

/**
 * Entrypoint.
 */
fun main() {
    // Let's create an animal robot with barking functionality
    val robot = AnimalRobot(BarkingAnimal())

    // Let's check if the robot can bark!
    println(robot.cry())
}
