/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkConjugateGradientOptimizer.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef __itkConjugateGradientOptimizer_h
#define __itkConjugateGradientOptimizer_h

#include "itkNonLinearOptimizer.h"
#include "vnl/algo/vnl_conjugate_gradient.h"

namespace itk
{
  
/** \class ConjugateGradientOptimizer
 * \brief Wrap of the vnl_conjugate_gradient to be adapted for Registration
 *
 */

  
template <class TCostFunction>
class ITK_EXPORT ConjugateGradientOptimizer : 
    public NonLinearOptimizer<TCostFunction> 

{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef ConjugateGradientOptimizer  Self;

  /**
   * Standard "Superclass" typedef.
   */
  typedef   NonLinearOptimizer<TCostFunction> Superclass;

  /** 
   * Smart pointer typedef support 
   */
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;



 /** 
   * Run-time type information (and related methods).
   */
  itkTypeMacro( ConjugateGradientOptimizer, 
      NonLinearOptimizer );


  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);
  

  /**
   * Method for getting access to the internal optimizer
   */
  vnl_conjugate_gradient & GetOptimizer(void);
 
  
  /** \class VnlCostFunction
   * \brief Adaptor between the CostFunction and the vnl_cost_function classes
   *
   */

  class VnlCostFunction : public vnl_cost_function
  {
  public:
      VnlCostFunction() { m_CostFunction=0; }    

      SetCostFunction( TCostFunction * ) 
        { m_CostFunction = costFunction; }
      

      /** 
       *  Delegate computation of the value to the CostFunction
       */
      virtual double f( const vnl_vector<double> & parameters ) {
        return m_CostFunction->GetValue( parameters );
      }
      
      /** 
       *  Delegate computation of the gradient to the CostFunction
       */
      virtual void gradf(const vnl_vector<double> & parameters,
                               vnl_vector<double> & gradient ) {
        gradient = m_CostFunction->GetDerivative( parameters );
      }
      
      /** 
       *  Delegate computation of value and gradient to the CostFunction
       */
      virtual void compute(const vnl_vector<double> & x,
                                 double * f, 
                                 vnl_vector<double> * g ) {
        // delegate the computation to the CostFunction
        f = m_CostFunction->GetValue( parameters );
        g = m_CostFunction->GetDerivative();
      }
 
  private:
      TCostFunction   * m_CostFunction;
  };  // end of Class CostFunction


  /**
   * Set the cost Function of type TCostFunction
   */
  SetCostFunction( TCostFunction * costFunction ) 
    { m_CostFunction->SetCostFunction( costFunction ); }
    
  

protected:

  ConjugateGradientOptimizer();
  virtual ~ConjugateGradientOptimizer() {};
  ConjugateGradientOptimizer(const Self&) {}
  void operator=(const Self&) {}

  vnl_conjugate_gradient     m_ConjugateGradient;

  VnlCostFunction            m_CostFunction;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkConjugateGradientOptimizer.txx"
#endif

#endif



