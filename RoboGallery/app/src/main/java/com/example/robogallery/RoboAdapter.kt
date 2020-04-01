package com.example.robogallery

import android.text.Layout
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.recyclerview.widget.RecyclerView
import com.example.robogallery.ui.main.MainViewModel
import com.squareup.picasso.Picasso
import kotlinx.android.synthetic.main.gallery_item.view.*

class RoboAdapter(private val viewModel: MainViewModel) : RecyclerView.Adapter<RoboAdapter.RoboViewHolder>() {

    var onItemClick : ((Int) -> Unit)? = null
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RoboViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val view = inflater.inflate(R.layout.gallery_item, parent, false)
        return RoboViewHolder(view)
    }

    override fun getItemCount(): Int {
        return viewModel.getSize()
    }

    override fun onBindViewHolder(holder: RoboViewHolder, position: Int) {
        holder.bind(viewModel.getPhoto(position))
    }

    inner class RoboViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView){
        init {
            itemView.setOnClickListener {
                onItemClick?.invoke(adapterPosition)
            }
        }
        fun bind(roboItem: RoboItem) {
            Log.i("Robot url : ", RoboApi.getPhoto(roboItem))
            Picasso.get()
                .load(RoboApi.getPhoto(roboItem))
                .placeholder(R.drawable.loading_animation)
                .into(itemView.image)
        }
    }

}

