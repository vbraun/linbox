/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.27
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package samples.quickstart.service.adb.xsd;

public class linboxfunctions {
  public static boolean det(SWIGTYPE_p_std__istream matrix_in, SWIGTYPE_p_std__ostream det_out) {
    return linboxfunctionsJNI.det(SWIGTYPE_p_std__istream.getCPtr(matrix_in), SWIGTYPE_p_std__ostream.getCPtr(det_out));
  }

  public static long detFiles(String matfile) {
    return linboxfunctionsJNI.detFiles(matfile);
  }

  public static boolean rank(SWIGTYPE_p_std__istream matrix_in, SWIGTYPE_p_std__ostream rank_out) {
    return linboxfunctionsJNI.rank(SWIGTYPE_p_std__istream.getCPtr(matrix_in), SWIGTYPE_p_std__ostream.getCPtr(rank_out));
  }

  public static int rankFiles(String matfile) {
    return linboxfunctionsJNI.rankFiles(matfile);
  }

  public static boolean val(SWIGTYPE_p_std__istream matrix_in, SWIGTYPE_p_std__ostream trace_out) {
    return linboxfunctionsJNI.val(SWIGTYPE_p_std__istream.getCPtr(matrix_in), SWIGTYPE_p_std__ostream.getCPtr(trace_out));
  }

  public static int valFiles(String matfile) {
    return linboxfunctionsJNI.valFiles(matfile);
  }

  public static boolean trace(SWIGTYPE_p_std__istream matrix_in, SWIGTYPE_p_std__ostream trace_out) {
    return linboxfunctionsJNI.trace(SWIGTYPE_p_std__istream.getCPtr(matrix_in), SWIGTYPE_p_std__ostream.getCPtr(trace_out));
  }

  public static int traceFiles(String matfile) {
    return linboxfunctionsJNI.traceFiles(matfile);
  }

}