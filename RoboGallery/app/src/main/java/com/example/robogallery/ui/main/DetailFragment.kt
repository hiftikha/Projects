package com.example.robogallery.ui.main

import android.content.Context
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProviders
import com.example.robogallery.*
import com.example.robogallery.databinding.DetailFragmentBinding
import com.squareup.picasso.Picasso

class DetailFragment : Fragment() {

    private lateinit var binding: DetailFragmentBinding
    private lateinit var viewModel: MainViewModel

    companion object {
        fun newInstance() = DetailFragment()
        const val SELECTED_ROBOT = "selectedRobot"
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        binding = DetailFragmentBinding.inflate(inflater, container, false)
        setupUI()
        return binding.root
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        initializeUI()
        arguments?.getInt(SELECTED_ROBOT)?.let {
            viewModel.setSelectedRobot(it)
        }
    }

    fun setupUI() {
        with(binding) {
            val robot = viewModel.getPhoto(viewModel.getSelectedRobot())
            Picasso.get()
                .load(RoboApi.getPhoto(robot))
                .placeholder(R.drawable.loading_animation)
                .into(image)
            label.text = robot.searchTerm
            delete.setOnClickListener {
                viewModel.removePhoto(viewModel.getSelectedRobot())
                activity?.onBackPressed()
            }
        }
    }

    private fun initializeUI() {
        val factory = InjectorUtils.provideQuotesViewModelFactory()
        viewModel = ViewModelProviders.of(this, factory).get(MainViewModel::class.java)
    }
}