#!/bin/bash
# This script is used for starting searcher
# Author : yindewei@jd.com
# Date   : 2016/07/25
#

SYS_CMD_DIR="/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"
export PATH=${PATH}:${SYS_CMD_DIR}

# global variable value
SERV_NAME=searcher_server
SERV_PATH=/export/App/jd_search/searcher/server
LOG_PATH=/export/Logs/jd_search/searcher
SHELL_SUFFIX=$(basename $0)
SHELL_LOG="${LOG_PATH}/${SHELL_SUFFIX}_for_${SERV_NAME}.log"
SELF=${SERV_PATH}/bin/${SHELL_SUFFIX}
START_SERVER_RUN=${SERV_PATH}/bin/start_server.sh

MERGER_CONFIG_TOOL_PATH="/export/App/conf_merger/conf_merger.py"
MERGER_CONFIG_engine="${SERV_PATH}/engine_conf/"
MERGER_CONFIG_RANK="${SERV_PATH}/rank_conf/"
MERGER_ROLE_FILE=${SERV_PATH}/conf/role.conf

if [ ! -d ${LOG_PATH} ];then
    mkdir -p ${LOG_PATH}
fi

function timenow
{
    echo "$(date +"%Y-%m-%d %H:%M:%S")"
}

function log_print
{
    WORDS=$*
    echo "${WORDS}" | tee -a ${SHELL_LOG}
}

function generate_conf
{

    if [ ! -e ${MERGER_CONFIG_TOOL_PATH} ]; then
        log_print "[$(timenow)] ${MERGER_CONFIG_TOOL_PATH} does not exis"
        exit 1
    fi

    if [ ! -e ${MERGER_ROLE_FILE} ]; then
        log_print "[$(timenow)] ${MERGER_ROLE_FILE} does not exis"
        exit 2
    fi

    log_print "Run config gen tools"
    python ${MERGER_CONFIG_TOOL_PATH} -c ${MERGER_CONFIG_engine} -r $(cat ${MERGER_ROLE_FILE}) -o ${SERV_PATH}/conf/ -v >> ${SHELL_LOG}
    if [[ $? != 0 ]]; then
        log_print "[$(timenow)] Run config gen error, pls check your ${MERGER_CONFIG_engine} folder"
        exit 3
    fi

    python ${MERGER_CONFIG_TOOL_PATH} -c ${MERGER_CONFIG_RANK} -r $(cat ${MERGER_ROLE_FILE}) -o ${SERV_PATH}/conf/ -v >> ${SHELL_LOG}
    if [[ $? != 0 ]]; then
        log_print "[$(timenow)] Run config gen error, pls check your ${MERGER_CONFIG_RANK} folder"
        exit 4
    fi
}

function main
{
    echo "=====>[$(timenow)] ${SHELL_SUFFIX} run" >> ${SHELL_LOG}

    # generator config file for server
    generate_conf

    # used for j-one
    #ENV_NOT_RESTART="yes"
    if [ "yes" = "$ENV_NOT_RESTART" ];then
        log_print "[$(timenow)] ENV_NOT_RESTART is equal to yes, starting terminated"
        exit 0
    fi

    if [ ! -e ${START_SERVER_RUN} ];then
        log_print "[$(timenow)] ERRORT:${START_SERVER_RUN} does not exist"
        return 1
    fi
    if [ ! -x ${START_SERVER_RUN} ];then
        chmod +x ${START_SERVER_RUN}
    fi

    nohup ${START_SERVER_RUN} -f >/dev/null 2>&1 &

    log_print "[$(timenow)] ${START_SERVER_RUN} executed"

    return 0
}

main $*
exit $?

# ------------- end ------------- #
