package com.example.robogallery.ui.main

import android.content.Context
import android.os.Bundle
import android.util.Log
import android.view.*
import android.view.inputmethod.EditorInfo
import android.widget.RadioButton
import android.widget.SearchView
import android.widget.Switch
import android.widget.Toast
import androidx.appcompat.widget.SwitchCompat
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProviders
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.robogallery.*
import com.example.robogallery.databinding.MainFragmentBinding
import kotlinx.android.synthetic.main.main_fragment.*


class MainFragment : Fragment() {

    private lateinit var roboAdapter: RoboAdapter
    private lateinit var binding: MainFragmentBinding

    private lateinit var listener : FragmentListener

    companion object {
        fun newInstance() = MainFragment()
    }

    private lateinit var viewModel: MainViewModel

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View {
        binding = MainFragmentBinding.inflate(inflater, container, false)
        initializeUI()
        setHasOptionsMenu(true)
        setupUI()
        return binding.root
    }

    override fun onActivityCreated(savedInstanceState: Bundle?) {
        super.onActivityCreated(savedInstanceState)
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        try {
            listener = context as FragmentListener
        } catch (castException : ClassCastException) {
            Log.e("ClassCastException: ", "Activity does not implement listener")
        }
    }

    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        inflater.inflate(R.menu.search, menu)
        val searchView = SearchView(context)
        val search = menu.findItem(R.id.action_search).apply {
            actionView = searchView
        }
        if (search != null) {
            val queryTextListener = object : SearchView.OnQueryTextListener {
                override fun onQueryTextSubmit(query: String?): Boolean {
                    if (query != null) {
                        searchView.clearFocus()
                        viewModel.addPhoto(query, viewModel.getSet())
                    }
                    return true
                }

                override fun onQueryTextChange(newText: String?): Boolean {
                    return true
                }

            }
            searchView.setOnQueryTextListener(queryTextListener)
        }
        super.onCreateOptionsMenu(menu, inflater)
    }

    private fun setupUI() {
        roboAdapter = RoboAdapter(viewModel)
        roboAdapter.onItemClick = {
            listener.showDetailsFragment(it)
        }
        with(binding) {
            gallery.adapter = roboAdapter
            gallery.layoutManager = GridLayoutManager(context, 3)
        }
        configureSetSwitches()
    }

    private fun initializeUI() {
        val factory = InjectorUtils.provideQuotesViewModelFactory()
        viewModel = ViewModelProviders.of(this, factory).get(MainViewModel::class.java)
    }

    private fun configureSetSwitches() {
        with(binding) {
            setOnCheckedListener(set1, 1)
            setOnCheckedListener(set2, 2)
            setOnCheckedListener(set3, 3)
        }
    }

    private fun handleSwitches(switchOffOne: Switch, switchOffTwo: Switch) {
        switchOffOne.isChecked = false
        switchOffTwo.isChecked = false
    }

    private fun setOnCheckedListener(switch : Switch, set: Int) {
        switch.setOnCheckedChangeListener{ buttonView, isChecked ->
            if (isChecked) {
                viewModel.setSet(set)
                with(binding) {
                    when(set) {
                        1 -> handleSwitches(set2, set3)
                        2 -> handleSwitches(set1, set3)
                        3 -> handleSwitches(set1, set2)
                    }
                }
            }
            with(binding) {
                if (!set1.isChecked && !set2.isChecked && !set3.isChecked) {
                    viewModel.resetSet()
                }
            }
        }
    }
}
