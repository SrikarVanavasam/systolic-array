// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VMATMUL_H_
#define _VMATMUL_H_  // guard

#include "verilated.h"

//==========

class Vmatmul__Syms;

//----------

VL_MODULE(Vmatmul) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(ld_weight,0,0);
    VL_IN(in_data[3],31,0);
    VL_IN(in_weights[3],31,0);
    VL_OUT(out_sum[3],31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    IData/*31:0*/ matrix_multiply__DOT__mu_top__DOT__weight;
    IData/*31:0*/ matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__DOT__weight;
    IData/*31:0*/ matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__DOT__weight;
    IData/*31:0*/ matrix_multiply__DOT__genblk2__BRA__1__KET____DOT__mu_row__DOT__weight;
    IData/*31:0*/ matrix_multiply__DOT__genblk2__BRA__2__KET____DOT__mu_row__DOT__weight;
    IData/*31:0*/ matrix_multiply__DOT__genblk3__BRA__1__KET____DOT__mu_col__DOT__weight;
    IData/*31:0*/ matrix_multiply__DOT__row_wire[9];
    IData/*31:0*/ matrix_multiply__DOT__col_wire[9];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__mu_top__out_sum;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__mu_top__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_sum;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_sum;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk1__BRA__2__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_sum;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_sum;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_sum;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_data;
    IData/*31:0*/ matrix_multiply__DOT____Vcellout__genblk3__BRA__2__KET____DOT__mu_col__out_data;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vmatmul__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vmatmul);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vmatmul(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vmatmul();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vmatmul__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vmatmul__Syms* symsp, bool first);
  private:
    static QData _change_request(Vmatmul__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vmatmul__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vmatmul__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vmatmul__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(Vmatmul__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vmatmul__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
