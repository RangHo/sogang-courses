package dev.rangho.capstone.hw3_2

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.RecyclerView

import io.github.serpro69.kfaker.faker

const val ITEM_COUNT = 100

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Populate the list of items
        val dataset = faker { }.aquaTeenHungerForce
        var itemList = ArrayList<Item>()
        for (i in 1..ITEM_COUNT) {
            itemList.add(Item(dataset.quote()))
        }

        // Find the recycler view
        val recyclerView = findViewById<RecyclerView>(R.id.recycler_view)
        recyclerView.adapter = ItemAdapter(this, itemList)
    }
}