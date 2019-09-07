package com.verkada.harooniftikhar.verkada;

import android.support.annotation.Nullable;

public enum  VerkadaError {
    /** Request could not be completed because that part of the library is incomplete. */
    NOT_IMPLEMENTED(-11, "Not Implemented", false, null),

    /** Request could not be completed due to incorrect parameter(s). */
    INVALID_PARAMETER(-4, "Invalid Parameter", false, "Ensure all inputs are valid"),

    /** Request failed because server is disconnected. */
    NO_SERVER_CONNECTION(-3, "No Connection", false, "Check your internet connection"),

    /** Request completed without error, but with no results. */
    NEGATIVE_SUCCESS(-1, "Success (No Result)", true, null),

    /** Successful action */
    SUCCESS(0, "Success", true, null);



    private final String desc, suggestion;
    private final boolean success;
    private final int id;
    VerkadaError(int _id, String _val, boolean isSuccess, String _suggestion){
        id = _id; desc = _val; success = isSuccess; suggestion = _suggestion;
    }

    /** Get the "display description" for this {@code VerkadaError} */
    public String getDescription(){ return desc; }

    /** Get the "helpful suggestion" for this {@code VerkadaError} (note: may be Null) */
    @Nullable
    public String getSuggestion(){ return suggestion; }

    /** Get the message ID code (for internal use only) */
    public int getID(){
        return id;
    }

}
