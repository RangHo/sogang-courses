package dev.rangho.capstone.hw3_1.data

import android.util.Log
import androidx.databinding.ObservableBoolean
import androidx.databinding.ObservableField
import androidx.databinding.ObservableInt
import androidx.lifecycle.ViewModel
import dev.rangho.capstone.hw3_1.R
import java.text.NumberFormat
import kotlin.math.ceil

class CapstoneViewModel : ViewModel() {

    var cost = ObservableField<String>()

    var rateId = ObservableInt()

    var tip = ObservableField<String>()

    var roundUp = ObservableBoolean()

    init {
        cost.set("0")
        rateId.set(R.id.option_twenty_percent)
        tip.set("")
        roundUp.set(false)
    }

    fun onCalculate() {
        val costDouble = cost.let { cost.get()!!.ifEmpty { "0" } }.toDouble()
        val rateDouble = when (rateId.get()) {
            R.id.option_twenty_percent -> 1.2
            R.id.option_eighteen_percent -> 1.18
            R.id.option_fifteen_percent -> 1.15
            else -> 1.0
        }

        var result = costDouble * rateDouble
        result = if (roundUp.get()) { ceil(result) } else { result }

        tip.set("Tip amount: " + NumberFormat.getCurrencyInstance().format(result))
    }
}