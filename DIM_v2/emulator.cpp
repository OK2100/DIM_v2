#include "emulator.h"

Emulator::Emulator(QObject *parent) : QObject(parent)
{
    serv = new MyDimServer(node);
//    serv->startServer();
}

Emulator::~Emulator()
{
//    serv->stopServer();
}

void Emulator::SetupConnection()
{
    connect(serv,&MyDimServer::set_ADC_ZERO_requested,serv,&MyDimServer::update_new_ADC_ZERO);
    connect(serv,&MyDimServer::set_ADC_DELAY_requested,serv,&MyDimServer::update_new_ADC_DELAY);
    connect(serv,&MyDimServer::set_ADC0_OFFSET_requested,serv,&MyDimServer::update_new_ADC0_OFFSET);
    connect(serv,&MyDimServer::set_ADC1_OFFSET_requested,serv,&MyDimServer::update_new_ADC1_OFFSET);
    connect(serv,&MyDimServer::set_ADC0_RANGE_requested,serv,&MyDimServer::update_new_ADC0_RANGE);
    connect(serv,&MyDimServer::set_ADC1_RANGE_requested,serv,&MyDimServer::update_new_ADC1_RANGE);
    connect(serv,&MyDimServer::set_TIME_ALIGN_requested,serv,&MyDimServer::update_new_TIME_ALIGN);
    connect(serv,&MyDimServer::set_CFD_THRESHOLD_requested,serv,&MyDimServer::update_new_CFD_THRESHOLD);
    connect(serv,&MyDimServer::set_CFD_ZERO_requested,serv,&MyDimServer::update_new_CFD_ZERO);
    connect(serv,&MyDimServer::set_THRESHOLD_CALIBR_requested,serv,&MyDimServer::update_new_THRESHOLD_CALIBR);

    connect(serv,&MyDimServer::set_CH_MASK_requested,serv,&MyDimServer::update_new_CH_MASK);
    connect(serv,&MyDimServer::set_CFD_SATR_requested,serv,&MyDimServer::update_new_CFD_SATR);
    connect(serv,&MyDimServer::set_OR_GATE_requested,serv,&MyDimServer::update_new_OR_GATE);

    connect(serv,&MyDimServer::set_TG_PATTERN_1_requested,serv,&MyDimServer::update_new_TG_PATTERN_1);
    connect(serv,&MyDimServer::set_TG_PATTERN_0_requested,serv,&MyDimServer::update_new_TG_PATTERN_0);
    connect(serv,&MyDimServer::set_TG_CONT_VALUE_requested,serv,&MyDimServer::update_new_TG_CONT_VALUE);

    connect(serv,&MyDimServer::set_TG_BUNCH_FREQ_requested,serv,&MyDimServer::update_new_TG_BUNCH_FREQ);
    connect(serv,&MyDimServer::set_TG_FREQ_OFFSET_requested,serv,&MyDimServer::update_new_TG_FREQ_OFFSET);

    connect(serv,&MyDimServer::set_DG_TRG_RESPOND_MASK_requested,serv,&MyDimServer::update_new_DG_TRG_RESPOND_MASK);
    connect(serv,&MyDimServer::set_DG_BUNCH_PATTERN_requested,serv,&MyDimServer::update_new_DG_BUNCH_PATTERN);
    connect(serv,&MyDimServer::set_DG_BUNCH_FREQ_requested,serv,&MyDimServer::update_new_DG_BUNCH_FREQ);
    connect(serv,&MyDimServer::set_DG_FREQ_OFFSET_requested,serv,&MyDimServer::update_new_DG_FREQ_OFFSET);
    connect(serv,&MyDimServer::set_RDH_FEE_ID_requested,serv,&MyDimServer::update_new_RDH_FEE_ID);
    connect(serv,&MyDimServer::set_RDH_PAR_requested,serv,&MyDimServer::update_new_RDH_PAR);
    connect(serv,&MyDimServer::set_RDH_MAX_PAYLOAD_requested,serv,&MyDimServer::update_new_RDH_MAX_PAYLOAD);
    connect(serv,&MyDimServer::set_RDH_DET_FIELD_requested,serv,&MyDimServer::update_new_RDH_DET_FIELD);
    connect(serv,&MyDimServer::set_CRU_TRG_COMPARE_DELAY_requested,serv,&MyDimServer::update_new_CRU_TRG_COMPARE_DELAY);
    connect(serv,&MyDimServer::set_BCID_DELAY_requested,serv,&MyDimServer::update_new_BCID_DELAY);


    connect(serv,&MyDimServer::apply_TG_MODE_requested,serv,&MyDimServer::update_act_TG_MODE);
    connect(serv,&MyDimServer::apply_DG_MODE_requested,serv,&MyDimServer::update_act_DG_MODE);

    //  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    connect(serv,&MyDimServer::apply_ADC_ZERO_requested,this,&Emulator::update_request_act_ADC_ZERO);
    connect(serv,&MyDimServer::apply_ADC_DELAY_requested,this,&Emulator::update_request_act_ADC_DELAY);
    connect(serv,&MyDimServer::apply_ADC0_OFFSET_requested,this,&Emulator::update_request_act_ADC0_OFFSET);
    connect(serv,&MyDimServer::apply_ADC1_OFFSET_requested,this,&Emulator::update_request_act_ADC1_OFFSET);
    connect(serv,&MyDimServer::apply_ADC0_RANGE_requested,this,&Emulator::update_request_act_ADC0_RANGE);
    connect(serv,&MyDimServer::apply_ADC1_RANGE_requested,this,&Emulator::update_request_act_ADC1_RANGE);
    connect(serv,&MyDimServer::apply_TIME_ALIGN_requested,this,&Emulator::update_request_act_TIME_ALIGN);
    connect(serv,&MyDimServer::apply_CFD_THRESHOLD_requested,this,&Emulator::update_request_act_CFD_THRESHOLD);
    connect(serv,&MyDimServer::apply_CFD_ZERO_requested,this,&Emulator::update_request_act_CFD_ZERO);
    connect(serv,&MyDimServer::apply_THRESHOLD_CALIBR_requested,this,&Emulator::update_request_act_THRESHOLD_CALIBR);
    connect(serv,&MyDimServer::apply_ALLtoCh_requested,this,&Emulator::update_request_act_AlltoCh);

    connect(serv,&MyDimServer::apply_CH_MASK_requested,this,&Emulator::update_request_act_CH_MASK);
    connect(serv,&MyDimServer::apply_CFD_SATR_requested,this,&Emulator::update_request_act_CFD_SATR);
    connect(serv,&MyDimServer::apply_OR_GATE_requested,this,&Emulator::update_request_act_OR_GATE);
    connect(serv,&MyDimServer::apply_TG_PATTERN_1_requested,this,&Emulator::update_request_act_TG_PATTERN_1);
    connect(serv,&MyDimServer::apply_TG_PATTERN_0_requested,this,&Emulator::update_request_act_TG_PATTERN_0);
    connect(serv,&MyDimServer::apply_TG_CONT_VALUE_requested,this,&Emulator::update_request_act_TG_CONT_VALUE);
////    connect(serv,&MyDimServer::apply_TG_SEND_SINGLE_requested,this,&Emulator::update_request_act_);(quint8 PMid, quint32 val)
    connect(serv,&MyDimServer::apply_TG_BUNCH_FREQ_requested,this,&Emulator::update_request_act_TG_BUNCH_FREQ);
    connect(serv,&MyDimServer::apply_TG_FREQ_OFFSET_requested,this,&Emulator::update_request_act_TG_FREQ_OFFSET);
    connect(serv,&MyDimServer::apply_DG_TRG_RESPOND_MASK_requested,this,&Emulator::update_request_act_DG_TRG_RESPOND_MASK);
    connect(serv,&MyDimServer::apply_DG_BUNCH_PATTERN_requested,this,&Emulator::update_request_act_DG_BUNCH_PATTERN);
    connect(serv,&MyDimServer::apply_DG_BUNCH_FREQ_requested,this,&Emulator::update_request_act_DG_BUNCH_FREQ);
    connect(serv,&MyDimServer::apply_DG_FREQ_OFFSET_requested,this,&Emulator::update_request_act_DG_FREQ_OFFSET);
    connect(serv,&MyDimServer::apply_RDH_FEE_ID_requested,this,&Emulator::update_request_act_RDH_FEE_ID);
    connect(serv,&MyDimServer::apply_RDH_PAR_requested,this,&Emulator::update_request_act_RDH_PAR);
    connect(serv,&MyDimServer::apply_RDH_MAX_PAYLOAD_requested,this,&Emulator::update_request_act_RDH_MAX_PAYLOAD);
    connect(serv,&MyDimServer::apply_RDH_DET_FIELD_requested,this,&Emulator::update_request_act_RDH_DET_FIELD);
    connect(serv,&MyDimServer::apply_CRU_TRG_COMPARE_DELAY_requested,this,&Emulator::update_request_act_CRU_TRG_COMPARE_DELAY);
    connect(serv,&MyDimServer::apply_BCID_DELAY_requested,this,&Emulator::update_request_act_BCID_DELAY);
    connect(serv,&MyDimServer::apply_ALLtoPM_requested,this,&Emulator::update_request_act_AlltoPM);

    //  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    connect(this,&Emulator::set_cmnd_ADC_ZERO_requested,serv,&MyDimServer::update_act_ADC_ZERO);
    connect(this,&Emulator::set_cmnd_ADC_DELAY_requested,serv,&MyDimServer::update_act_ADC_DELAY);
    connect(this,&Emulator::set_cmnd_ADC0_OFFSET_requested,serv,&MyDimServer::update_act_ADC0_OFFSET);
    connect(this,&Emulator::set_cmnd_ADC1_OFFSET_requested,serv,&MyDimServer::update_act_ADC1_OFFSET);
    connect(this,&Emulator::set_cmnd_ADC0_RANGE_requested,serv,&MyDimServer::update_act_ADC0_RANGE);
    connect(this,&Emulator::set_cmnd_ADC1_RANGE_requested,serv,&MyDimServer::update_act_ADC1_RANGE);
    connect(this,&Emulator::set_cmnd_TIME_ALIGN_requested,serv,&MyDimServer::update_act_TIME_ALIGN);
    connect(this,&Emulator::set_cmnd_CFD_THRESHOLD_requested,serv,&MyDimServer::update_act_CFD_THRESHOLD);
    connect(this,&Emulator::set_cmnd_CFD_ZERO_requested,serv,&MyDimServer::update_act_CFD_ZERO);
    connect(this,&Emulator::set_cmnd_THRESHOLD_CALIBR_requested,serv,&MyDimServer::update_act_THRESHOLD_CALIBR);


    connect(this,&Emulator::set_cmnd_ADC0_MEANAMPL_requested,serv,&MyDimServer::update_act_ADC0_MEANAMPL);
    connect(this,&Emulator::set_cmnd_ADC1_MEANAMPL_requested,serv,&MyDimServer::update_act_ADC1_MEANAMPL);
    connect(this,&Emulator::set_cmnd_ADC0_ZEROLVL_requested,serv,&MyDimServer::update_act_ADC0_ZEROLVL);
    connect(this,&Emulator::set_cmnd_ADC1_ZEROLVL_requested,serv,&MyDimServer::update_act_ADC1_ZEROLVL);
    connect(this,&Emulator::set_cmnd_CFD_CNT_requested,serv,&MyDimServer::update_act_CFD_CNT);
    connect(this,&Emulator::set_cmnd_TRG_CNT_requested,serv,&MyDimServer::update_act_TRG_CNT);
    connect(this,&Emulator::set_cmnd_RAW_TDC_DATA_requested,serv,&MyDimServer::update_act_RAW_TDC_DATA);

    connect(this,&Emulator::set_cmnd_CH_MASK_requested,serv,&MyDimServer::update_act_CH_MASK);
    connect(this,&Emulator::set_cmnd_CFD_SATR_requested,serv,&MyDimServer::update_act_CFD_SATR);
    connect(this,&Emulator::set_cmnd_OR_GATE_requested,serv,&MyDimServer::update_act_OR_GATE);

    connect(this,&Emulator::set_cmnd_TG_PATTERN_1_requested,serv,&MyDimServer::update_act_TG_PATTERN_1);
    connect(this,&Emulator::set_cmnd_TG_PATTERN_0_requested,serv,&MyDimServer::update_act_TG_PATTERN_0);
    connect(this,&Emulator::set_cmnd_TG_CONT_VALUE_requested,serv,&MyDimServer::update_act_TG_CONT_VALUE);
    connect(this,&Emulator::set_cmnd_TG_BUNCH_FREQ_requested,serv,&MyDimServer::update_act_TG_BUNCH_FREQ);
    connect(this,&Emulator::set_cmnd_TG_FREQ_OFFSET_requested,serv,&MyDimServer::update_act_TG_FREQ_OFFSET);

    connect(this,&Emulator::set_cmnd_DG_TRG_RESPOND_MASK_requested,serv,&MyDimServer::update_act_DG_TRG_RESPOND_MASK);
    connect(this,&Emulator::set_cmnd_DG_BUNCH_PATTERN_requested,serv,&MyDimServer::update_act_DG_BUNCH_PATTERN);
    connect(this,&Emulator::set_cmnd_DG_BUNCH_FREQ_requested,serv,&MyDimServer::update_act_DG_BUNCH_FREQ);
    connect(this,&Emulator::set_cmnd_DG_FREQ_OFFSET_requested,serv,&MyDimServer::update_act_DG_FREQ_OFFSET);
    connect(this,&Emulator::set_cmnd_RDH_FEE_ID_requested,serv,&MyDimServer::update_act_RDH_FEE_ID);
    connect(this,&Emulator::set_cmnd_RDH_PAR_requested,serv,&MyDimServer::update_act_RDH_PAR);
    connect(this,&Emulator::set_cmnd_RDH_MAX_PAYLOAD_requested,serv,&MyDimServer::update_act_RDH_MAX_PAYLOAD);
    connect(this,&Emulator::set_cmnd_RDH_DET_FIELD_requested,serv,&MyDimServer::update_act_RDH_DET_FIELD);
    connect(this,&Emulator::set_cmnd_CRU_TRG_COMPARE_DELAY_requested,serv,&MyDimServer::update_act_CRU_TRG_COMPARE_DELAY);
    connect(this,&Emulator::set_cmnd_BCID_DELAY_requested,serv,&MyDimServer::update_act_BCID_DELAY);

    connect(this,&Emulator::set_cmnd_BOARD_STATUS_requested,serv,&MyDimServer::update_act_BOARD_STATUS);
    connect(this,&Emulator::set_cmnd_TEMPERATURE_requested,serv,&MyDimServer::update_act_TEMPERATURE);
    connect(this,&Emulator::set_cmnd_HDMI_LINK_requested,serv,&MyDimServer::update_act_HDMI_LINK);
    connect(this,&Emulator::set_cmnd_BITS_requested,serv,&MyDimServer::update_act_BITS);
    connect(this,&Emulator::set_cmnd_READOUT_MODE_requested,serv,&MyDimServer::update_act_READOUT_MODE);
    connect(this,&Emulator::set_cmnd_BCID_SYNC_MODE_requested,serv,&MyDimServer::update_act_BCID_SYNC_MODE);
    connect(this,&Emulator::set_cmnd_RX_PHASE_requested,serv,&MyDimServer::update_act_RX_PHASE);
    connect(this,&Emulator::set_cmnd_CRU_ORBIT_requested,serv,&MyDimServer::update_act_CRU_ORBIT);
    connect(this,&Emulator::set_cmnd_CRU_BC_requested,serv,&MyDimServer::update_act_CRU_BC);
    connect(this,&Emulator::set_cmnd_RAW_FIFO_requested,serv,&MyDimServer::update_act_RAW_FIFO);
    connect(this,&Emulator::set_cmnd_SEL_FIFO_requested,serv,&MyDimServer::update_act_SEL_FIFO);
    connect(this,&Emulator::set_cmnd_SEL_FIRST_HIT_DROPPED_ORBIT_requested,serv,&MyDimServer::update_act_SEL_FIRST_HIT_DROPPED_ORBIT);
    connect(this,&Emulator::set_cmnd_SEL_LAST_HIT_DROPPED_ORBIT_requested,serv,&MyDimServer::update_act_SEL_LAST_HIT_DROPPED_ORBIT);
    connect(this,&Emulator::set_cmnd_SEL_HITS_DROPPED_requested,serv,&MyDimServer::update_act_SEL_HITS_DROPPED);
    connect(this,&Emulator::set_cmnd_READOUT_RATE_requested,serv,&MyDimServer::update_act_READOUT_RATE);
}

void Emulator::FillActRandom()
{

    for(quint8 iPM=1;iPM<=serv->Npms;iPM++) {
        for(quint8 iCH=1;iCH<=serv->pm[iPM-1]->Nchannels;iCH++) {
            emit set_cmnd_ADC_ZERO_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC_DELAY_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC0_OFFSET_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC1_OFFSET_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC0_RANGE_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC1_RANGE_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_TIME_ALIGN_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_CFD_THRESHOLD_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_CFD_ZERO_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_THRESHOLD_CALIBR_requested(iPM,iCH,qrand()%1000);

            emit set_cmnd_ADC0_MEANAMPL_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC1_MEANAMPL_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC0_ZEROLVL_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_ADC1_ZEROLVL_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_CFD_CNT_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_TRG_CNT_requested(iPM,iCH,qrand()%1000);
            emit set_cmnd_RAW_TDC_DATA_requested(iPM,iCH,qrand()%1000);
        }

        emit set_cmnd_CH_MASK_requested(iPM,qrand()%1000);
        emit set_cmnd_CFD_SATR_requested(iPM,qrand()%1000);
        emit set_cmnd_OR_GATE_requested(iPM,qrand()%1000);

        emit set_cmnd_TG_PATTERN_1_requested(iPM,qrand()%1000);
        emit set_cmnd_TG_PATTERN_0_requested(iPM,qrand()%1000);
        emit set_cmnd_TG_CONT_VALUE_requested(iPM,qrand()%1000);
        emit set_cmnd_TG_BUNCH_FREQ_requested(iPM,qrand()%1000);
        emit set_cmnd_TG_FREQ_OFFSET_requested(iPM,qrand()%1000);

        emit set_cmnd_DG_TRG_RESPOND_MASK_requested(iPM,qrand()%1000);
        emit set_cmnd_DG_BUNCH_PATTERN_requested(iPM,qrand()%1000);
        emit set_cmnd_DG_BUNCH_FREQ_requested(iPM,qrand()%1000);
        emit set_cmnd_DG_FREQ_OFFSET_requested(iPM,qrand()%1000);
        emit set_cmnd_RDH_FEE_ID_requested(iPM,qrand()%1000);
        emit set_cmnd_RDH_PAR_requested(iPM,qrand()%1000);
        emit set_cmnd_RDH_MAX_PAYLOAD_requested(iPM,qrand()%1000);
        emit set_cmnd_RDH_DET_FIELD_requested(iPM,qrand()%1000);
        emit set_cmnd_CRU_TRG_COMPARE_DELAY_requested(iPM,qrand()%1000);
        emit set_cmnd_BCID_DELAY_requested(iPM,qrand()%1000);

        emit set_cmnd_BOARD_STATUS_requested(iPM,qrand()%1000);
        emit set_cmnd_TEMPERATURE_requested(iPM,qrand()%1000);
        emit set_cmnd_HDMI_LINK_requested(iPM,qrand()%1000);
        emit set_cmnd_BITS_requested(iPM,qrand()%1000);
        emit set_cmnd_READOUT_MODE_requested(iPM,qrand()%1000);
        emit set_cmnd_BCID_SYNC_MODE_requested(iPM,qrand()%1000);
        emit set_cmnd_RX_PHASE_requested(iPM,qrand()%1000);
        emit set_cmnd_CRU_ORBIT_requested(iPM,qrand()%1000);
        emit set_cmnd_CRU_BC_requested(iPM,qrand()%1000);
        emit set_cmnd_RAW_FIFO_requested(iPM,qrand()%1000);
        emit set_cmnd_SEL_FIFO_requested(iPM,qrand()%1000);
        emit set_cmnd_SEL_FIRST_HIT_DROPPED_ORBIT_requested(iPM,qrand()%1000);
        emit set_cmnd_SEL_LAST_HIT_DROPPED_ORBIT_requested(iPM,qrand()%1000);
        emit set_cmnd_SEL_HITS_DROPPED_requested(iPM,qrand()%1000);
        emit set_cmnd_READOUT_RATE_requested(iPM,qrand()%1000);
    }

}


//((qrand() % ((h+1)-l))+l)
